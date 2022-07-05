#include<bits/stdc++.h>
using namespace std;
#define int_max 1000000009

int graph[1000][1000]; int parent[1000][1000]; int q[1000]; int f=0,r=-1; int n,m; int dist[1000]; int inx[1000]; int nodes[1000];
                        //graph stores the social network
                        //parent[i] stores all parents of ith node which leads to shortest path
                        //q implements queue in bfs
                        // f is front index and r is rear index in q
                        //n is no. of nodes
                        //m is no. of edges
                        //dist[i] is distance of node i from s
                        //inx[i] is no of parent nodes if node i
                        //nodes[i] stores frequency of occurrence of node i

int size;               //no. of shortest paths from s to e

struct node{

	int val;             //val is total no.of occurrence of that node in all shortest path
	int x;               //x is node no.
};

int partition(node arr[],int lo,int hi){        //partition function of quicksort

	int x=lo;
	while(lo<=hi){

		while(arr[lo].val>=arr[x].val)
		lo++;

		while(arr[hi].val<arr[x].val)
		hi--;

		if(lo<=hi){
		node t=arr[lo];
		arr[lo]=arr[hi];
		arr[hi]=t;
	    }

	}
	node k=arr[hi];
	arr[hi]=arr[x];
	arr[x]=k;

	return hi;

}
int quick(node arr[],int lo,int hi){                //quicksort

	if(hi>lo){

		int j=partition(arr,lo,hi);
		quick(arr,lo,j-1);
        quick(arr,j+1,hi);

	}

}

void parent_path(int u,int s,int path[],int **paths,int j){     //function to store all possible shortest path in paths

	if(u==s){                                                   //base condition
		for(int p=0;p<=j;p++){                                  //stores a shortest path in paths
		paths[size][p]=path[p];
		}
		size++;
	return;
    }

	for(int i=0;i<inx[u];i++){                                  //for every parent of u

	if(parent[u][i]!=s)
	nodes[parent[u][i]]++;                                      //increments the frequency of occurrence of that particular node

	path[j]=parent[u][i];

	parent_path(parent[u][i],s,path,paths,j+1);                 //recursive call
	}
}

void bfs(int v){                        //bfs starting from source node

	for(int i=1;i<=n;i++){

		if(graph[v][i]){                //succ i of node v

			if(dist[i]>dist[v]+1){

			dist[i]=dist[v]+1;
			q[++r]=i;                   //push i into queue

			inx[i]=0;
			parent[i][inx[i]++]=v;      //parent if i is v
			}
			else{

				if(dist[i]==dist[v]+1)
				parent[i][inx[i]++]=v;
			}
		}
	}

	if(f<=r)                    //f is front index and r is rear index of q
	bfs(q[f++]);                //while queue is not empty

}


int main(){

    cout<<"No of nodes: ";
	cin>>n;              //n (no of nodes) and  m (no. of edges)
    cout<<"No of edges: ";
    cin>>m;

	cout<<"Input graph:"<<endl;
	for(int i=0;i<m;i++){   //construction of graph

		int a,b; cin>>a>>b;

		graph[a][b]=1;
		graph[b][a]=1;
	}

	cout<<endl;

	cout<<"Source node: ";
	int s,e; cin>>s;            //s is source and e is destination
    cout<<"Destination node: ";
    cin>>e;

    cout<<endl;

	for(int i=1;i<=n;i++)   //initializes distance of every node from s as infinite
	dist[i]=int_max;

	dist[s]=0;              //distance of s from itself
	parent[s][0]=-1;        //parent of s is initialized to -1(null)
	inx[s]=1;               //no of parents of s is 1(which is -1)

	bfs(s);

    int path[dist[e]];      //length of shortest path from s to e is dist[e]

	int **paths;             //array of all the path array from s to e

	paths=(int **)malloc(1000*sizeof(int *));

	for(int i=0;i<1000;i++)
	paths[i]=(int *)malloc(sizeof(int)*dist[e]);

	size=0;                 //no. of shortest path from s to e is initialized to 0

	parent_path(e,s,path,paths,0);

	node arr[n];

	for(int i=1;i<=n;i++){
	arr[i].val=nodes[i];
	arr[i].x=i;
    }

    quick(arr,1,n);

    cout<<"All shortest paths between source and destination:"<<endl;
	for(int i=0;i<size;i++){

		for(int j=dist[e]-1;j>=0;j--)
		cout<<paths[i][j]<<" ";

		cout<<e;

		cout<<"\n";
	}
	cout<<endl;

	cout<<"Nodes that are prone to infection in decreasing order with their frequency of occurrence: "<<endl;

    for(int i=1;i<=n;i++){

    cout<<arr[i].x<<" "<<arr[i].val<<"\n";
	}

	cout<<endl;
	
	cout<<"Following nodes have maximum chance of getting infected : "; 
	int f=0;
	for(int i=1;i<=n;i++){
	if(arr[i].val==arr[1].val && arr[1].val != 0){
	cout<<arr[i].x<<" ";
	f=1;
    }
	else
	break;
    }
    if(f==0)
    cout<<"No such node exists";
    cout<<"\n";
}
