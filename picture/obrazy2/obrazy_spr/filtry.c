#include<stdio.h>
#include<stdlib.h>
#include"struktura.h"

void negatyw(t_obraz *obraz){
    int i,j;
    int (*piksele)[obraz->wym_x]; 
    piksele=(int(*)[obraz->wym_x]) obraz->piksele; 

    for(i=0;i<obraz->wym_y; i++){
        for(j=0;j<obraz->wym_x;j++){
            piksele[i][j]=obraz->odcieni-piksele[i][j];}}
}

void progowanie(t_obraz *obraz, int prog){
    int i,j;
    int (*piksele)[obraz->wym_x]; 
    piksele=(int(*)[obraz->wym_x]) obraz->piksele; 

    prog=(obraz->odcieni)*prog/100;

    for(i=0;i<obraz->wym_y; i++){
        for(j=0;j<obraz->wym_x;j++){
            if(piksele[i][j]>=prog) piksele[i][j]=obraz->odcieni;
            else piksele[i][j]=0;}}
}

void konturowanie(t_obraz *obraz){
    int i,j;
    int (*piksele)[obraz->wym_x]; 
    piksele=(int(*)[obraz->wym_x]) obraz->piksele;    

    for(i=0;i<obraz->wym_y; i++){
        for(j=0;j<obraz->wym_x;j++){
            if(i==0&&j<obraz->wym_x) piksele[i][j]=abs(piksele[i][j+1]-piksele[i][j]);
                if(i!=0&&j<obraz->wym_x) piksele[i][j]=abs(piksele[i][j+1]-piksele[i][j])+abs(piksele[i+1][j]-piksele[i][j]);
                if(j==obraz->wym_x) piksele[i][j]=abs(piksele[i+1][j]-piksele[i][j]);
                if(piksele[i][j]>obraz->odcieni) piksele[i][j]=obraz->odcieni;}}
}

void rozmycie(t_obraz *obraz){
    int i,j,tmp=0;
    int (*piksele)[obraz->wym_x]; 
    piksele=(int(*)[obraz->wym_x]) obraz->piksele; 

    for(i=0;i<obraz->wym_y; i++){
        for(j=0;j<obraz->wym_x;j++){
        if(j==0) piksele[i][j]=(piksele[i][j]+piksele[i][j+1])/2;
            if(j==obraz->wym_x-1) piksele[i][j]=(tmp+piksele[i][j])/2;
            if(j!=0&&j!=obraz->wym_x-1) piksele[i][j]=(tmp+piksele[i][j]+piksele[i][j+1])/3;
            tmp=piksele[i][j];}}
}

void zmiana_poziomow(t_obraz *obraz, int czern, int biel){
    int i,j;
    int (*piksele)[obraz->wym_x]; 
    piksele=(int(*)[obraz->wym_x]) obraz->piksele; 
    czern=czern*obraz->odcieni/100;
    biel=biel*obraz->odcieni/100;

    for(i=0;i<obraz->wym_y; i++){
        for(j=0;j<obraz->wym_x;j++){
            if(piksele[i][j]<=czern) piksele[i][j]=0;
            else{if(piksele[i][j]<biel) piksele[i][j]=(piksele[i][j]-czern)*obraz->odcieni/(biel-czern);
            else piksele[i][j]=obraz->odcieni;}
        }}
}
