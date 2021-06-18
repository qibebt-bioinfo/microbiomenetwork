# A scale-free, fully connected global transition network underlies known microbiome diversity

## Description
Microbiomes are inherently linked by their structural similarity, yet the global patterns and features of such similarity are not clear. Here we propose a search-based microbiome transition network to probe the microbiome similarity globally. By  traversing a composition-similarity based network of 177,022 microbiomes, we show that although their compositions are distinct by habitat, each microbiome is on-average only seven neighbors from any other microbiome on Earth, indicating the inherent homology of microbiome at global scale. This network is scale-free, suggesting a high degree of stability and robustness in microbiome transition. By tracking the minimum spanning tree in this network, a global roadmap of microbiome dispersal was derived that tracks the potential formulation of microbial diversity. Such search-based global microbiome networks, reconstructed within hours on just one computing node, provide a readily expanded reference for tracing the origin and evolution of existing or new microbiome datasets. 

## Data source
The meta-data of the 177,022 samples is available [meta-data](meta-data.txt).
### The distribution of samples among the habitats
<table>
	<tr>
	    <th>Sample type</th>
	    <th>Habitat</th>
	    <th>Number of samples</th>  
	</tr >
	<tr >
	    <td rowspan="6">Human associated</td>
	    <td>Gut</td>
	    <td>51,076</td>
	</tr>
	<tr>
	    <td>Skin</td>
	    <td>19,455</td>
	</tr>
	<tr>
	    <td>Oral</td>
	    <td>10,896</td>
	</tr>
	<tr>
	    <td>Ohter human body-site</td>
	    <td>3,018</td>
	</tr>
	<tr>
	    <td>Urogenital</td>
	    <td>1,204</td>
	</tr>
	<tr>
	    <td>Nose</td>
	    <td>489</td>
	</tr>
	<tr >
	    <td rowspan="2">Animal associated</td>
	    <td>Mammal animal</td>
	    <td>29,918</td>
	</tr>
	<tr>
	    <td>Non-mammal animal</td>
	    <td>11,172</td>
	</tr>
	<tr >
	    <td rowspan="10">Environmental</td>
	    <td>Building</td>
	    <td>11,248</td>
	</tr>
	<tr>
	    <td>Soil</td>
	    <td>10,507</td>
	</tr>
	<tr>
	    <td>Marine water</td>
	    <td>6,090</td>
	</tr>
	<tr>
	    <td>Lake</td>
	    <td>4,234</td>
	</tr>
	<tr>
	    <td>Plant</td>
	    <td>3,456</td>
	</tr>
	<tr>
	    <td>Freshwater</td>
	    <td>3,112</td>
	</tr>
	<tr>
	    <td>River</td>
	    <td>2,248</td>
	</tr>
	<tr>
	    <td>Milk</td>
	    <td>1,636</td>
	</tr>
	<tr>
	    <td>Sand</td>
	    <td>968</td>
	</tr>
	<tr>
	    <td>Food</td>
	    <td>780</td>
	</tr>
	<tr >
	    <td rowspan="2">Other</td>
	    <td>Other</td>
	    <td>4,074</td>
	</tr>
	<tr>
	    <td>Mock</td>
	    <td>811</td>
	</tr>
	<tr>
	    <td align="center" colspan="2">Total</td>
	    <td>177,022</td>
	</tr>
</table>

## About the `Figure` folder
This folder includes all the data necessary for generating the Figures. 

## About the `Code` folder
This is an implementation of the Microbiomenetwork. This folder contains all of scripts for Closure, Dijkstra and MST( Minimum-cost Spanning Tree) analysis.

### Requirements
* g++ (GCC) >= 4.8.5
* Python >= xxx

### Closure
A closure is a set of nodes (microbiomes), in which each microbiome can traverse to any other one by direct or indirect transitions (with finite steps). 
a. Compile
```
cd closure
g++ closure.cpp -o closure
```
b. Run
```
./closure query.out closure.out 0.868
```
in which "query.out" is the search results from MSE, "closure.out" the closure result and "0.868" is the the statistical threshold of the significant high value to define the direct transition
### Dijkstra
Dijkstra algorithm is used to compute the pairwise shortest transition steps of all sample pairs in the main closure. 

a. Python Environment

For statistical analysis of the microbiome transition network, the python scripts requires python3 and "igraph" package (https://igraph.org/python/) which can be installed using pip:
```
pip install python-igraph
```

b. Run

```
python3 get_diameter.py query.out diameter.txt
```
in which "query.out" is the search results from MSE, the first line of diameter.txt is the diameter (the maximum number of edges in the shortest path between any pair of its nodes) of the microbiome transition network, and the next line is the nodes in the shortest path.

```
python Dijkstra.py query.out shortest_path
```
in which "query.out" is the search results from MSE. It will produce two result files, "shortest_path.info" and "shortest_path.value", which respectively includes a matrix represents the shortest path between every pair of nodes in the network and its length. If a pair of nodes are unconnected, it will be represented by "oo" and "inf" in the two files.


### MST (Minimum-cost Spanning Tree)
The “microbial dispersal” roadmap can be derived by parsing the Minimum Spanning Tree (MST) of the main closure using the Kruskal algorithm. 
a. Compile
```

```
b. Run
