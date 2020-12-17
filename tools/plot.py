#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import argparse


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
    radius = int(data.split("\n")[0])
    for v in data.split("\n")[1:-1]:
        solution.append(list(map(int, v.split(" "))))
    return (nodes, demand, solution, radius)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot solution")
    parser.add_argument('nodes', type=str, help="Nodes file")
    parser.add_argument('demand', type=str, help="Demand file")
    parser.add_argument('solution', type=str, help="Solution file, you can generate it by redirecting the output of ./mclp")

    args = parser.parse_args()

    (nodes, demand, solution, radius) = parse_files(args.nodes, args.demand, args.solution)

    x, y = zip(*nodes)
    fig, ax = plt.subplots()

    ax.scatter(x, y, s=demand)
    for sol in solution:
        circ = plt.Circle(sol, radius, color='r', fill=False)
        ax.add_artist(circ)
    ax.set_aspect('equal')

    fig.savefig("out.png", dpi=300)

