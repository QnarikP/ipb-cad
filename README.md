# ipb-cad

Coursework for **Computação de Alto Desempenho (CAD)** at Instituto Politécnico de Bragança. The course covers shared-memory programming with POSIX threads and distributed-memory programming with MPI.

The local folder is `Projects/IPB/CAD`. The GitHub repository is [QnarikP/ipb-cad](https://github.com/QnarikP/ipb-cad) so it stays distinct from other IPB projects (`COC`, `RE`, `Thesis`).

## Layout

Your solutions are under `2 - pthreads/exercises`. Course slides, setup guides, and lecture notes stay on this machine and are not in the repository. Professor source under each part’s `given/` directory is also left out. Compiled binaries are ignored.

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
