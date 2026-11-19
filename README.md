# cFS CDH Demo App (`cdh_app`)

A small NASA core Flight System (cFS) application that demonstrates command
and data handling (CDH) concepts for a student lunar rover mission concept
exploring a permanently shadowed region (PSR).

> **Concept demo on a simulated Linux target — not flight software.**
> All thresholds and values are generic placeholders.

## Status

- [x] App builds and runs in the current cFS bundle (`native_std` target)
- [x] Own message IDs, separate from NASA's sample_app
- [x] `NOOP`, `RESET_COUNTERS`, and `SET_THRESHOLD` (typed payload) commands
- [x] Commands use CCSDS packet format (supports CDH-008)
- [ ] Housekeeping telemetry includes threshold and mode
- [ ] Store records until ground acknowledges receipt + `ACK_DOWNLINK` (CDH-001)
- [ ] Tag each record with simulated position and depth (CDH-002)
- [ ] `SAFE_MODE` command: stop recording, keep stored data (CDH-009)
- [ ] Simulated battery + Return-to-Sunlight via cFS LC and SC (CDH-004)
- [ ] Stored command sequence for a PSR traverse via cFS SC (CDH-003)

## Commands

| Command | Code | Payload | Effect |
|---|---|---|---|
| NOOP | 0 | none | Sends an event with the app version |
| RESET_COUNTERS | 1 | none | Resets command counters |
| SET_THRESHOLD | 4 | `int32 Threshold` | Sets the recording threshold |

Command message ID: `0x18D0`

## Build

Tested on Ubuntu 24.04 (arm64) with the current `nasa/cFS` bundle.

1. Clone cFS:
   ```
   git clone --recurse-submodules https://github.com/nasa/cFS.git
   cd cFS
   ```
2. Clone this repo into the apps folder:
   ```
   git clone https://github.com/audreykcc/cfs-cdh-demo.git apps/cdh_app
   ```
3. Register the app:
   - `sample_defs/targets.cmake`: add `cdh_app` to `MISSION_GLOBAL_APPLIST`
   - `sample_defs/generate_startup.cmake`: add
     ```
     "CFE_APP, cdh_app,     CDH_APP_Main,       CDH_APP,      50,   32768, 0x0, 0;\n"
     ```
4. Build:
   ```
   make native_std.prep
   make native_std.install
   ```

## Run and test

Terminal 1:
```
cd build-native_std/exe/cpu1
./core-cpu1
```

Terminal 2:
```
cd tools/cFS-GroundSystem/Subsystems/cmdUtil
make
./cmdUtil --host=127.0.0.1 --endian=LE --pktid=0x18D0 --cmdcode=0
./cmdUtil --host=127.0.0.1 --endian=LE --pktid=0x18D0 --cmdcode=4 --long=42
```

Expected output in Terminal 1:
```
CDH_APP 3: CDH: NOOP command ...
CDH_APP 13: CDH: Threshold set to 42
```

## Credits and license

Based on NASA's [sample_app](https://github.com/nasa/sample_app), part of the
[core Flight System](https://github.com/nasa/cFS). Licensed under the Apache
License 2.0. See [LICENSE](LICENSE).

Author: Audrey Criss
