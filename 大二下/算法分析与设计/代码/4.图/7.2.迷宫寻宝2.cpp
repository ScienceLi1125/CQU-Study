/* Created by LiJia */
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
//const int maxN = 100;
#define Wall '#'
#define Road '@'
#define Start 'S'
#define Goal 'G'

class Status{
public:
    short x,y; //在迷宫位置
    bool crossed; //是否越过宝物箱
    short key; //已拿到的宝物
    int steps; //到达该位置划分的时间
    
    Status(short xx=0, short yy=0, bool cs=false, short k=0, int s=0){
        x = xx;
        y = yy;
        crossed = cs;
        key = k;
        steps = s;
    }
    Status(const Status& A){
        x = A.x;
        y = A.y;
        crossed = A.crossed;
        key = A.key;
        steps = A.steps;
    }
    const Status& operator=(const Status& A){
        x = A.x;
        y = A.y;
        crossed = A.crossed;
        key = A.key;
        steps = A.steps;
        return *this;
    }
};
////////
template <typename T>
class Queue{
private:
    int maxSize;
    int size;
    T* array;
    int front, rear;
    
    void init(){
        size = rear = 0;
        front = 1;
    }
    
public:
    Queue(int sz){
        maxSize = sz + 1;
        array = new T[maxSize];
        init();
    }
    ~Queue(){
        delete[] array;
    }
    bool isEmpty() const{
        return size == 0;
    }
    void push(const T& e){
        if((++rear) == maxSize)
            rear = 0;
        array[rear] = e;
        size++;
    }
    T pop(){
        T tmp = array[front++];
        if(front == maxSize) front = 0;
        size--;
        return tmp;
    }
    int length() const{
        return size;
    }
    void clear(){
        init();
    }
    
};
/////
inline bool isWall(char c){
    return c == Wall;
}
inline bool isKey(char c){
    return ('a'<=c) && (c<='z');
}
inline bool isValidKey(char c, short key){
    return (c-'a'-key) == 0;
}
//////
int BFS(const string* maze, short N, short K){
    const short xd[] = {-1,0,1, 0};
    const short yd[] = { 0,1,0,-1};
    
    bool visited[N][N][K+1];
    memset(visited, false, sizeof(visited));
    Queue<Status> queue(N*N*(K+1));
    
    for(int i=1; i<N-1; i++){
        for(int j=1; j<N-1; j++){
            if(maze[i][j] == Start){
                queue.push(Status(i,j));
                i = N;
                break;
            }
        }
    }
    
    while(queue.length()){
        Status st = queue.pop();
        if(maze[st.x][st.y] == Goal && st.key == K)
            return st.steps;
        
        if(visited[st.x][st.y][st.key]) continue;
        
        if(isKey(maze[st.x][st.y]) && !st.crossed){
            if(isValidKey(maze[st.x][st.y], st.key)){
                //cout << maze[st.x][st.y] << " " << st.key+1 << " "<< st.steps+1 << endl;
                visited[st.x][st.y][st.key++] = true;
            }
            st.steps++;
            st.crossed = true;
            queue.push(st);
            continue;
        }
        
        visited[st.x][st.y][st.key] = true;
        
        for(short k=0; k<4; k++){
            //
            short nx = st.x+xd[k];
            short ny = st.y + yd[k];
            
            if(isWall(maze[nx][ny])) continue;
            if(visited[nx][ny][st.key]) continue;
            queue.push(Status(nx,ny,false,st.key,st.steps+1));
           
        }
        
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    /*
    string dir = "/Users/lijia/Documents/programs/c++/maze/";
    cout << "file name of test case:\n";
    string fn;
    cin >> fn;
    ifstream ift(dir+fn);
    short N,K;
    ift >> N >> K;
    cout << N << " " << K << endl;
    string maze[N];
    for(int i=0; i<N; i++)
        ift >> maze[i];
    ift.close();
    */
    
    short N,K;
    cin >> N >> K;
    string maze[N];
    for(int i=0; i<N; i++)
        cin >> maze[i];
    
    cout << BFS(maze, N, K) << endl;
  
    return 0;
}