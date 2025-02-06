import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

def create_barabasi_albert(initial_nodes,new_nodes):
    graph = nx.complete_graph(initial_nodes)
    for i in range(new_nodes):
        new_node = initial_nodes + i
        graph.add_node(new_node)
        for node in graph:
            if new_node == node:
                continue
            probality = len(graph[node])/len(graph)
            if probality <= np.random.random():
                graph.add_edge(new_node,node)
    return graph



if __name__ == '__main__':
    barabasi = create_barabasi_albert(2,100)
    print(barabasi)
    
    # pos = nx.spring_layout(barabasi)
    # nx.draw_networkx_nodes(barabasi,pos)
    # nx.draw_networkx_edges(barabasi,pos)
    # plt.show()
    histo_data = []
    for degree in nx.degree(barabasi):
        print(degree[1])
        histo_data.append(degree[1])
    plt.hist(histo_data)
    plt.show()
    pass