#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import argparse
from pathlib import Path

def eucl_distance(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return np.sqrt(x*x + y*y)


def parse_files(nodes, demand, solution):
    with open(nodes, "r") as f:
        data = f.read()
    nodes = []
    # in both cases, the last character is a newline so we need to ignore the
    # last splitted value.
    for v in data.split("\n")[1:]:
        if v == "":
            continue
        nodes.append(list(map(int, v.split(" "))))

    with open(demand, "r") as f:
        data = f.read()

    demand = list(map(int, data.split("\n")[:-1]))

    with open(solution, "r") as f:
        data = f.read()

    solution = []
    current_score = int(data.split("\n")[0])
    radius = int(data.split("\n")[1])
    for v in data.split("\n")[2:-1]:
        solution.append(list(map(int, v.split(" "))))
    return (nodes, demand, solution, radius, current_score)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot solution")
    parser.add_argument('nodes', type=str, help="Nodes file")
    parser.add_argument('demand', type=str, help="Demand file")
    parser.add_argument('solution', type=str, help="Solution file, you can generate it by redirecting the output of ./mclp")

    args = parser.parse_args()

    print(f"Plotting {args.solution}")

    (nodes, demand, solution, radius, current_score) = parse_files(args.nodes, args.demand, args.solution)

    # Add a color index
    for node in nodes:
        node.append(-1)

    for i, sol in enumerate(solution):
        for node in nodes:
            if eucl_distance(node, sol) <= radius:
                node[2] = i

    scale = 1.5
    fig, ax = plt.subplots(figsize=(6*scale, 5*scale))

    nodes = np.array(nodes)
    demand = np.array(demand)

    # First draw the ones that weren't considered
    mask = nodes[:, 2] == -1
    _nodes = nodes[mask]
    _demand = demand[mask]
    if _nodes.size > 0:
        x, y, _ = zip(*_nodes)
        ax.scatter(x, y, s=_demand, label=f"Not considered", alpha=0.5)
    for i, sol in enumerate(solution):
        mask = nodes[:, 2] == i
        _nodes = nodes[mask]
        _demand = demand[mask]

        if _nodes.size > 0:
            x, y, _ = zip(*_nodes)
            ax.scatter(x, y, s=_demand, label=f"Considered by solution {i}")

    for sol in solution:
        x, y = sol
        ax.scatter(x, y, marker="x", color="r")
        circ = plt.Circle((x, y), radius, color='r', fill=False)
        ax.add_artist(circ)


    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5))

    ax.set_aspect('equal')
    ax.set_title(f"Current score: {current_score}")

    plt.tight_layout()

    filename = Path(args.solution).resolve().name
    fig.savefig(f"{filename}.png", dpi=300)

