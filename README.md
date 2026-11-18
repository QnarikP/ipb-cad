# ipb-cad

Coursework for **Computação de Alto Desempenho (CAD)** at Instituto Politécnico de Bragança. The course covers shared-memory programming with POSIX threads and distributed-memory programming with MPI.

The local folder is `Projects/IPB/CAD`. The GitHub repository is [QnarikP/ipb-cad](https://github.com/QnarikP/ipb-cad) so it stays distinct from other IPB projects (`COC`, `RE`, `Thesis`).

## Layout

| Path | Contents |
| --- | --- |
| `0 - misc/docs` | Cluster SSH setup and VS Code for C on Linux |
| `1 - introduction/docs` | Part 1 slides: motivation and key concepts |
| `1 - introduction/notes` | Lecture transcript (2026-09-29) and Anki deck |
| `2 - pthreads/docs` | POSIX threads slides, exercise sheets, November practical |
| `2 - pthreads/exercises` | Solutions written and run for the pthreads exercises |
| `3 - mpi` | MPI programming slides |

Professor source drops live under each part’s `given/` directory and are kept out of the commits. Compiled binaries (`.exe` and extensionless build outputs) are ignored.

## Pthreads exercises

| Directory | Exercise |
| --- | --- |
| `pt5_collatz` | Collatz, serial and threaded |
| `pt6` | PT06 |
| `pt10` | Leibniz pi, serial and parallel |
| `pt12` | Count odd values in a vector, with timing |
| `pt13` | Parallel odd-count and `benchmark.sh` |
| `pt_20` | Shared counter, mutex, and condition variable |
| `pt_22` | Cyclic Leibniz variant |
| `pt_23` | PT23 |

Pthreads programs are built with `-pthread`, for example:

```bash
gcc solution.c -pthread -o solution
./solution
```
