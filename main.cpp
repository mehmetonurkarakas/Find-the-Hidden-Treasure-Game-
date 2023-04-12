#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void deleteArray(int** arr,int row){ //Deleting the dynamic array
    for (int i = 0; i < row; i++){
            delete[] arr[i];
        }
    delete[] arr;
}

void game(int** gameArr,int ** keyArr,int rowSize,int columnSize,int keySize,int centerRow,int centerColumn,string out){
    ofstream output;
    output.open(out.c_str(),ios::app);
    int move = (keySize-1)/2;// I did it for moving on map
    int point = 0;
    for (int i = 0; i < keySize; i++) // calculating point in here 
    {
        for (int j = 0; j < keySize; j++)
        {      
            point+=gameArr[centerRow+i-move][centerColumn+j-move]*keyArr[i][j];
        }    
    }
    
    
    output << centerRow << "," << centerColumn << ";" << point << endl;
  
    int direction = point%5;
    if (direction<0)
    {
        direction +=5;
    }
    

    if (direction == 1) // go up
    {
        if (centerRow==move)
        {
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow+keySize,centerColumn,out);
        }
        else{
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow-keySize,centerColumn,out);        
        }
    }
    else if (direction == 2) // go down
    {
        if(centerRow== rowSize - move-1) // Last index is size-1 so ı gotta write -1
        {           
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow-keySize,centerColumn,out);
        }
        else {
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow+keySize,centerColumn,out);
        }
         
    }
    else if (direction == 3) // go right
    {
        if (centerColumn == columnSize-move-1)// Last index is size-1 so ı gotta write -1
        {
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow,centerColumn-keySize,out);
        }
        else{
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow,centerColumn+keySize,out);
        }
    }
    else if (direction == 4) // go left
    {
        if (centerColumn == move)
        {
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow,centerColumn+keySize,out);
        }
        else
        {
            game(gameArr,keyArr,rowSize,columnSize,keySize,centerRow,centerColumn-keySize,out);
        }    
    }
}

int ** tablePlacing(string Matrix,int mapRowSize,int mapColumnSize){ // This method splitting for txt and carry to array.
 

    ifstream mapFile;
    mapFile.open(Matrix.c_str());

    int **mapTable = new int *[mapRowSize];  // Dynamic array and placing map matrix to this array.
    for (int i = 0; i < mapRowSize; i++)
    {
        mapTable[i] = new int[mapColumnSize];
    }


    int i = 0,j = 0;
    char seperate = ' ';
    string temp;string line1;
    while (getline(mapFile, line1)) // reading line by line 
    {
        stringstream ss(line1);
        while (getline(ss, temp, seperate))
        {
            stringstream s(temp);
            int value;
            s >> value;
            mapTable[i][j] = value;
            j++;
        }
        i++;
        j = 0;
    }
    mapFile.close();

    return mapTable;
}


int main(int argc, char* argv[]) {

    
    string tempMapSize = argv[1];
    int ray[2] ;
    string tem;
    stringstream strs(tempMapSize);
    int i= 0;
    while(getline(strs,tem,'x')){
        stringstream strst(tem);
        int value;
        strst >> value;
        ray[i] = value;
        i++;
    }
    i = 0;
    int mapRowSize = ray[0];
    int mapColumnSize = ray[1];
 
    int keyMapSize;
    string temp2 = argv[2];
    stringstream s1(temp2);
    s1 >> keyMapSize;

    string mapMatrix = argv[3];string keyMatrix = argv[4];string outputFile = argv[5];

    int **mapTable = tablePlacing(mapMatrix,mapRowSize,mapColumnSize); // creating maptable
    int **keyTable = tablePlacing(keyMatrix,keyMapSize,keyMapSize); // creating keytable
    int centerRow = (keyMapSize-1)/2,centerColumn = (keyMapSize-1)/2; // I used center indexes for move on table

    game(mapTable,keyTable,mapRowSize,mapColumnSize,keyMapSize,centerRow,centerColumn,outputFile);

    deleteArray(mapTable,mapRowSize);
    deleteArray(keyTable,keyMapSize);

    return 0;
}

