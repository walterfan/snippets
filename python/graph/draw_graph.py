from graphviz import Digraph
from graphviz import Source

dot = Digraph(comment="flowchart",node_attr={'shape': 'box'})
dot.format = 'png'
dot.graph_attr['rankdir'] = 'LR'
dot.node('start', 'Start')
dot.node('hello', 'Hello')
dot.node('end', 'End')

dot.edge('start', 'hello')
dot.edge('hello', 'end')

print(dot.source)

dot.render('./flow_chart.png', view=False)  

src = Source.from_file('./test_graph.dot')
src.render('./test_graph.png', view=True)