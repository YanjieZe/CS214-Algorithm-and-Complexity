#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.



int sum(int a[], int n)
{
    int sum=0;
    for(int i=0; i<n; ++i)
        sum += a[i];
    return sum;
}

void print_matrix(vector< vector<int> > matrix)
{
    int row_num = matrix.size();
    int col_num = matrix[0].size();
    for(int i=0; i<row_num; ++i)
    {
        cout<<'\n';
        for(int j=0; j<col_num; ++j)
            cout<<' '<<matrix[i][j];
    }
    cout<<'\n';
}

/* reverse the original graph*/
void reverse_graph(vector< vector<int> > &adjacent_matrix)
{
    int size=adjacent_matrix.size();

    for(int i=0; i<size; ++i)
        for(int j=i; j<size; ++j)
        {
            if(adjacent_matrix[i][j]==1 && adjacent_matrix[j][i]==0) 
            {
                adjacent_matrix[i][j] = 0;
                adjacent_matrix[j][i] = 1;        
            }
            else if(adjacent_matrix[i][j]==0 && adjacent_matrix[j][i]==1)
            {
                adjacent_matrix[i][j] = 1;
                adjacent_matrix[j][i] = 0;
            }
            
        }
}


/* Based on the edge, construct the adjacent matrix */
void construct_adjacent_matrix(vector< vector<int> > &adjacent_matrix, vector<pair<int,int> >& edge)
{
    int begin;
    int end;

    for(int i=0; i<edge.size(); ++i)
    {
        begin = edge[i].first;
        end = edge[i].second;
        adjacent_matrix[begin][end] = 1;
    }
}


/* Depth First Search, give the id of the vertex with largest post number*/
void DFS_find_source(int visit_vertex, vector<vector<int> > &adjacent_matrix, int post_number_recorder[], int prev_number_recorder[], int is_deleted[], int &clock)
{
    if(prev_number_recorder[visit_vertex]!=0)
        return;
    if(is_deleted[visit_vertex])
        return;
    else
    {// previsit
        clock++;
        prev_number_recorder[visit_vertex] = clock;
    }

    for(int i=0; i<adjacent_matrix.size(); ++i)
    {
        if(adjacent_matrix[visit_vertex][i]==1)
            DFS_find_source(i, adjacent_matrix, post_number_recorder, prev_number_recorder,is_deleted,  clock);
    }
    clock++;
    post_number_recorder[visit_vertex] = clock;
  
    //cout<<"Visit of Vertex "<< visit_vertex <<" is finished, with post number="<<clock<<endl;
    return;
}



/* Based on the vertex, delete the whole component*/
void delete_component(int source_vertex, vector< vector<int> > &adjacent_matrix, int is_deleted[])
{
    if(is_deleted[source_vertex]==1)
        return;
    is_deleted[source_vertex]=1;
    //cout<<'('<<source_vertex<<')'<<endl;
    for(int i=0; i<adjacent_matrix.size(); ++i)
    {   
        if(adjacent_matrix[source_vertex][i]==1)
        {
            delete_component(i, adjacent_matrix, is_deleted);
        }      
    }

}

/* find a source node of a component
return the id of vertex */
int find_source_vertex(int start_point, vector< vector<int> > &adjacent_matrix, int is_deleted[])
{
    int vertex_num = adjacent_matrix.size();

    reverse_graph(adjacent_matrix);

    int recorder[vertex_num];
    int prev_recorder[vertex_num];
    int clock=0;
    for(int i=0; i<vertex_num; ++i)
        recorder[i]=0, prev_recorder[i]=0;
    //cout<<"Begin find a source vetex of component..."<<endl;

    DFS_find_source(start_point, adjacent_matrix, recorder, prev_recorder, is_deleted, clock);
    int max_post_number=0, vertex_id=-1;
    for(int i=0; i<vertex_num; ++i)
        if(recorder[i]>max_post_number)
            max_post_number = recorder[i], vertex_id=i;
    delete_component(vertex_id, adjacent_matrix, is_deleted);
    reverse_graph(adjacent_matrix);
    
    cout<<"Find a source vertex: "<<vertex_id<<endl;



    return vertex_id;
}



/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
int SCC(int n, vector<pair<int,int> >& edge) {
    int edge_num = edge.size();

    // create an adjacent matrix
    vector< vector<int> > adjacent_matrix(n);
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
            adjacent_matrix[i].push_back(0);
    }
    construct_adjacent_matrix(adjacent_matrix, edge);
            

    int num_components = 0;
    int is_deleted[n];
    int start_point=0;
    for(int i = 0; i<n; ++i)
        is_deleted[i] = 0;
    int sum_delete;
    while ((sum_delete=sum(is_deleted, n))!=n)
    {   
        for(int i=0; i<n; ++i)
            if(is_deleted[i]!=1)
            {
             start_point = i;
             break;
            }
      
        int id = find_source_vertex(start_point, adjacent_matrix, is_deleted);
        num_components++;
    }
    cout<<"Number of components: "<<num_components<<endl;
    return num_components;
}



// n vertex, m edge
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int> > edge;
    ifstream fin;
    ofstream fout;
    fin.open("test.in");
    cout<<fin.is_open()<<endl;
    fin>>n>>m;
    cout<<n<<" "<<m<<endl;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
