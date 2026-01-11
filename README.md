# COServerDat
Hook for load decrypted Server.dat in Conquer Online (Need other DLL for working login)

## Basic Usage
This DLL must be **injected into `Conquer.exe`**.  
Its purpose is to **intercept the loading of `Server.dat`** and replace its content at runtime with a custom uncrypted xml.

## Features
- Read from COServer.dat (bypass real server.dat)
- FPs Unlock (In all versions now)
- Screen Resolution Changes to FHD (1920x1024) (Only V5187 for now, that require a lot of work yet)

---

## Requirements

For the DLL to work correctly, the following files **must be present in the client directory**:

### 1. `version.dat`

The `version.dat` file **must contain a line starting with `#`**, which indicates the **real client version**.

Valid example:
`
99999
#6609
`

> The number after `#` is used to resolve the correct memory address depending on the client version.

---

### 2. `COServer.dat`

This file must contain:

- A **decrypted `Server.dat`**
- The corresponding **server XML**

The full content of `COServer.dat` is injected into memory when the client loads `Server.dat`.

---

## Notes

- The DLL automatically selects the correct memory address based on the version specified in `version.dat`.
- Compatible with multiple client versions without recompilation.
- Injection is performed at runtime without modifying original client files
- It is a technique that does not affect some 'flags' or internal resources, unlike other methods.
