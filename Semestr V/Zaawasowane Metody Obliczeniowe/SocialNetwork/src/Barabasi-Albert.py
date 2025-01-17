import networkx as nx
import matplotlib.pyplot as plt

nodes = [1,2,3]
edges = [(1,2),(1,3),(2,3)]

base_graph = nx.Graph()
base_graph.add_nodes_from(nodes)
base_graph.add_edges_from(edges)
bara_network = nx.barabasi_albert_graph(100,99)

nx.draw(bara_network)
plt.draw()