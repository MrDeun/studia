import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

def graph_summary(graph):
    print(graph)
    print("Promien grafu: {}".format(nx.radius(graph) if nx.is_connected(graph) else np.inf))
    print("Srednica grafu: {}".format(nx.diameter(graph) if nx.is_connected(graph) else np.inf))
    print("Maksymaly stopien grafu: {}".format(np.max(nx.degree(graph))))
    print("Sredni stopien grafu: {}".format(np.mean(nx.degree(graph))))
    histo_data = []
    for degree in nx.degree(barabasi):
        histo_data.append(degree[1])
    plt.hist(histo_data,bins=50)
    plt.show()

def create_barabasi_albert(initial_nodes,new_nodes):
    graph = nx.complete_graph(initial_nodes)
    for i in range(new_nodes):
        new_node = initial_nodes + i
        graph.add_node(new_node)
        for node in graph:
            if new_node == node:
                continue
            probality = float(len(graph[node])/len(graph))
            if probality >= np.random.random():
                graph.add_edge(new_node,node)
    return graph

def create_erdos_renyi(vertices, chance):
    graph = nx.Graph()
    graph.add_nodes_from(range(vertices))
    for node1 in graph:
        for node2 in graph:
            if node1 == node2:
                continue
            if chance >= np.random.random():
                graph.add_edge(node1,node2)
    return graph
    

def create_watts_strogats(node_count,near_neighbours_count,probality):
    graph = nx.Graph()
    graph.add_nodes_from(range(node_count))
    for node in range(len(graph)):
        for offset in range(-near_neighbours_count,near_neighbours_count+1):
            if offset == 0:
                continue
            graph.add_edge(node,(node+offset)%node_count)
    return graph

if __name__ == '__main__':
    erdos = create_erdos_renyi(1000,float(1/1000))
    watts = create_watts_strogats(1000,2,float(1/1000))
    barabasi = create_barabasi_albert(2,998)
    
    graph_summary(erdos)
    graph_summary(watts)
    graph_summary(barabasi)

    pass