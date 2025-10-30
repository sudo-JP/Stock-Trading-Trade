I use gpt to help format this

# Asset Sync & Observable Pipeline Roadmap (Python subscribes Rust)

This roadmap describes the pipeline from **C++ fetching Alpaca assets → Rust backend → Python subscribers**, using binary protocols, in-memory diffing, and bulk upserts.

---

## **Phase 1 — C++: Fetch & Serialize**
1. **Fetch all assets from Alpaca**
   - Use `/v2/assets` endpoint.
   - Optionally filter by `status == "active"` or `asset_class == "us_equity"`.

2. **Check against in-memory HashMap for any changes**
    - Map symbol fields to struct. 
    - See if there are any changes

3. **Serialize each asset to binary struct**
   - Map JSON fields to `AssetBinaryPayload`.
   - Encode strings as fixed-length byte arrays (pad/truncate).
   - Convert numeric fields to correct types (int64, float32/64).

4. **Pack into AoS**
   - Concatenate all structs into a contiguous buffer.
   - Prefix with `uint32_t length` = number of assets.

5. **Send to Rust backend**
   - Via TCP, Unix socket, or shared memory.
   - Rust receives the contiguous AoS buffer.

---

## **Phase 2 — Rust: In-Memory Cache & Diffing**
1. **Receive binary buffer from C++**
   - Read `uint32_t length` → number of structs.
   - Deserialize each chunk into `AssetBinaryPayload`.

2. **Maintain in-memory cache**
   - `HashMap<String, AssetBinaryPayload>` keyed by `symbol` or `asset_id`.
   - Acts as the canonical state of all assets.

3. **Diff against current state**
   - Compare incoming struct vs cached version.
   - Mark for insert if new, or update if any field changed.

4. **Bulk upsert to Postgres**
   - Batch changed/new assets (e.g., 100–500 rows).
   - Use `INSERT ... ON CONFLICT` to update existing rows.
   - Reduces DB write overhead.

5. **Notify subscribers (Python)**
   - Publish only changed/new assets via pub/sub (Redis, channels, or sockets).
   - Python receives updates reactively, no polling needed.

---

## **Phase 3 — Python: Subscribe & Compute**
1. **Subscribe to Rust updates**
   - Use Pub/Sub, socket, or other reactive mechanism.
   - Receive only changed/new assets as binary AoS buffer.

2. **Deserialize AoS buffer**
   - Split buffer into `n` chunks of `sizeof(AssetBinaryPayload)`.
   - Convert to dicts or keep as structs for computation.

3. **Compute derived features**
   - Risk metrics, ML features, sector aggregation, etc.
   - Optionally store computed features in separate DB or cache.

---

## **Phase 4 — Optional Optimizations**
- **Delta at C++**: Only send changed assets to Rust.
- **Batch notifications in Rust**: Reduce Pub/Sub message frequency.
- **Shared memory / memory-mapped buffers**: Minimize copying for large arrays.
- **Python local cache**: Keep last state to compute differences efficiently.

---

## **Data Flow Overview**
