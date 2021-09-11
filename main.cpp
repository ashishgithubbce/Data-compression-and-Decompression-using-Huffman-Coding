#include <iostream>
#include<vector>
using namespace std;
#include<unordered_map>
class tree{
 public:
    int freq;
    char C;
    tree *left;
    tree *right;
    tree(char ch, int val){
         C = ch;
         freq = val;
         left = NULL;
         right = NULL;
    }
};
void swapNode(vector < tree * > &heap, int i, int j){
            tree *temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
    return;
}
void MinHeapifyBottom(vector< tree * > &heap){
      int childIndx = heap.size()-1;
      while(childIndx >0 ){
          int parentIndx = (childIndx-1)/2;
                if(heap[childIndx]->freq <  heap[parentIndx]->freq){
                           swapNode(heap,childIndx,parentIndx);
                           childIndx = parentIndx;
                }
                else
                   break;
       }
    return;
}
void insertIntoHeap(vector<tree *> &heap, tree *node){
         heap.push_back(node);
         MinHeapifyBottom(heap);
}
void MinHeapifyTop(int indx, vector < tree * > &heap){
        int leftIndex  = 2*indx +1;
        int rightIndex = 2*indx +2;
        int minimalIndx = indx;
     if(leftIndex < (int)heap.size() && heap[indx]->freq > heap[leftIndex]->freq)
            minimalIndx = leftIndex;
     if(rightIndex <(int) heap.size() && heap[minimalIndx]->freq > heap[rightIndex]->freq )
            minimalIndx = rightIndex;

     if(minimalIndx!=indx){
            swapNode(heap,minimalIndx,indx);
            MinHeapifyTop(minimalIndx,heap);
   }
return;
}
tree *extractMin(vector < tree * > &heap){
      tree *minNode = heap[0];
      heap[0] = heap[heap.size()-1];
      heap.pop_back();
      MinHeapifyTop(0,heap);
      return minNode;

}
void buildHeap(vector < tree * > &heap){
    for(int i= (heap.size()/2) -1; i>=0;i--){
            MinHeapifyTop(i,heap);
    }
}
void HuffmanAlgorithm(vector< tree*> &heap){
     while(heap.size()!=1){
           tree *node1 = extractMin(heap);
           tree *node2 = extractMin(heap);
           int newFreq = node1->freq + node2->freq;
           tree *node  = new tree('\0',newFreq);
           node->left = node1;
           node->right = node2;
           insertIntoHeap(heap,node);
     }
   return ;
}
void printTree(tree *root){
      if(root ==NULL)
          return;
      cout<<root->freq<<" "<<root->C<<endl;
      printTree(root->left);
      printTree(root->right);
return;
}
void printHuffmanCode(tree *root, unordered_map <char ,string > &M,string &s){
    if(root->C !='\0'){
         M[root->C] = s;
         s.pop_back();
         return;
    }
    s.push_back('0');
    printHuffmanCode(root->left,M,s);
    s.push_back('1');
    printHuffmanCode(root->right,M,s);
    s.pop_back();
    return;

}
int main()
{
    string input;
    cout<<"Enter Input String"<<endl;
    cin>>input;
    unordered_map< char, int > CharacterFrequency;
    vector < tree * > heap;
    for(int i=0;i<(int)input.length();i++){
          CharacterFrequency[input[i]]++;
    }
    cout<<"Character Frequency Table:"<<endl;
    unordered_map< char, int >:: iterator it = CharacterFrequency.begin();
    while(it!=CharacterFrequency.end()){
          char c = it->first;
          int frequency = it->second;
          tree *node = new tree(c,frequency);
          heap.push_back(node);
          cout<<c<<":"<<frequency<<endl;
          it++;
    }
    buildHeap(heap);
    HuffmanAlgorithm(heap);
    cout<<endl<<"Huffman tree:"<<endl;
    printTree(heap[0]);
    cout<<"Huffman Code of each character:"<<endl;
    unordered_map <char ,string > Encode;
    string s;//to store huffman code of each character
    printHuffmanCode(heap[0],Encode,s);
    unordered_map <string,char > DecodeMap;
    unordered_map <char ,string > :: iterator i = Encode.begin();
    while(i!=Encode.end()){
        cout<<i->first<<":"<<i->second<<endl;
        DecodeMap[i->second] = i->first;
        i++;
    }
    cout<<endl<<"input:"<<input<<endl;
    string encodedString;
    for(int i=0;i<(int)input.length();i++){
        encodedString+=Encode[input[i]];
    }
    cout<<"compressed input string:"<<encodedString<<endl;
    string decodedString,temp;
    for(int i=0;i<(int)encodedString.length();i++){
          temp.push_back(encodedString[i]);
          if(DecodeMap.count(temp)>0){
                  decodedString.push_back(DecodeMap[temp]);
                  temp = "";
          }
    }
    cout<<"Decoded String:"<<decodedString<<endl;
    return 0;
}
