# echosrv
This is an echo server. You connect to it and send text and it sends (echoes) it back.

## Clases

| Name | Description |
|------|-------------|
| echosrv | The main echo server class<br>Handles all clients |
| mthreads | Thread pool library |
| mlog | Logging library |

## How to build

### Windows

Go into to root of this project and run:
```batch
cmake --build .
```
The executable is located in  ```Debug\echosrv.exe```
