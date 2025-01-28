from typing import List, Tuple, NoReturn, Optional
from collections import deque


def inside(pos: Tuple[int, int], rows: int, cols: int) -> bool:
    y, x = pos
    return 0 <= y < rows and 0 <= x < cols


def find_path(
    lab: List[List[str]], start: Tuple[int, int], end: Tuple[int, int]
) -> Optional[str]:

    INF = 1000 * 1000 * 5

    rows, cols = len(lab), len(lab[0])
    dist = [[INF] * cols for _ in range(rows)]

    q: deque[Tuple[int, int]] = deque([start])
    dist[start[0]][start[1]] = 0

    dir_x = [-1, 1, 0, 0]
    dir_y = [0, 0, -1, 1]

    while q:
        curr = q.popleft()

        for dir in range(len(dir_x)):
            next: Tuple[int, int] = (curr[0] + dir_y[dir], curr[1] + dir_x[dir])
            if not inside(next, rows, cols):
                continue

            if lab[next[0]][next[1]] == "#":
                continue

            next_dist = dist[next[0]][next[1]]
            curr_dist = dist[curr[0]][curr[1]]
            if next_dist > curr_dist + 1:
                dist[next[0]][next[1]] = curr_dist + 1
                q.append(next)

    if dist[end[0]][end[1]] == INF:
        return None

    # it should be ["L", "R", "U", "D"]
    # but we swap them to be easier to do append
    # because we go from end to start not the other way around
    dir_ch = ["R", "L", "D", "U"]
    q.append(end)

    sol = []
    while q:
        curr = q.popleft()

        if curr == start:
            break

        dir_id = 0
        min_dist = INF
        best_cell = end

        for dir in range(len(dir_x)):
            next: Tuple[int, int] = (curr[0] + dir_y[dir], curr[1] + dir_x[dir])
            if not inside(next, rows, cols):
                continue

            next_dist = dist[next[0]][next[1]]
            best_dist = dist[best_cell[0]][best_cell[1]]

            if next_dist < best_dist:
                best_cell = next
                dir_id = dir
                min_dist = next_dist

        q.append(best_cell)
        sol.append(dir_ch[dir_id])

    return "".join(sol[::-1])


def main() -> None:
    rows, cols = (int(x) for x in input().split())

    lab: List[List[str]] = []
    start = (0, 0)
    end = (0, 0)
    for i in range(rows):
        cells = list(input())
        for j in range(len(cells)):
            if cells[j] == "A":
                start = (i, j)
            elif cells[j] == "B":
                end = (i, j)

        lab.append(cells)

    path = find_path(lab, start, end)
    if path is None:
        print("NO")
    else:
        print("YES")
        print(len(path))
        print(path)

    return None


if __name__ == "__main__":
    main()
