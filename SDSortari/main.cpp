#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include<cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void random(vector<int>&v,int n,int mx)
{
    srand((unsigned)time(0));
    int a;
    for(int i = 0;i<n;i++)
    {
         a = rand()%mx;
         v.push_back(a);
    }
    cout<<"\n";
}
int sortat(vector<int>&v,int n)
{
    int i,ok=1;
    for(i=1;i<n;i++)
    {
        if(v[i]<v[i-1]){ok=0;}
    }
    return ok;
}

//RadixSort--O(n+k)
int nrmax(vector<int>&v,int n)//caut valoarea maxima din vector
{
    int mx = 0;
    for(int i=0;i<n;i++)
    {
        if(v[i]>mx){mx=v[i];}
    }
    return mx;
}
void counting(vector<int>&v,int n,int poz)
{
    int c[10],a[n],i;

    for(i=0;i<10;i++)
    {
        c[i]=0;
    }
    for(i=0;i<n;i++)//vector in care memorez cate numere au aceleasi cifre pe pozitia poz
    {
        c[(v[i]/poz)%10]++;
    }
    for(i=1;i<10;i++)
    {
        c[i] += c[i-1];
    }
    for(i=n-1;i>=0;i--)//sortez nr in functie de cifra de pe pozitia poz in vectorul a
    {
        a[c[(v[i]/poz)%10]-1] = v[i];
        c[(v[i]/poz)%10]--;
    }
    for(i=0;i<n;i++)//mut nr sortate din a inapoi in vectorul principal
    {
        v[i] = a[i];
    }
}
void RadixSort(vector<int>&v,int n)
{
    auto start0 = high_resolution_clock::now();
    int mx = nrmax(v,n),i;
    for(int poz = 1;mx/poz>0;poz= poz*10)
    {
        counting(v,n,poz);
    }
    auto stop0 = high_resolution_clock::now();
    auto duration0 = duration_cast<microseconds> (stop0 - start0);
    int ok=sortat(v,n);
    if(ok==1){cout<<"RadixSort a sortat corect. "<<"Timpul de rulare: "<<duration0.count()<<" microsecunde\n";}
    else{cout<<"RadixSort nu a sortat corect.\n";}

}

//MergeSort--O(n*logn)
void Merge(vector<int>&v,int st,int mij,int dr)
{
    int x,y,i,j,k;
    x = mij-st+1;
    y = dr-mij-1+1;
    int A[x],B[y]; //pune elementele din cele 2 parti din vector in 2 vectori distoncti
    for(i=0;i<x;i++)
    {
        A[i] = v[st+i];
    }
    for(i=0;i<y;i++)
    {
        B[i] = v[mij+1+i];
    }
    i = 0;
    j = 0;
    k = st;
    while(i<x && j<y) //sortez cei 2 vectori crescator punand elementele sortate in vectorul initial de la pozitia st la dr
    {
        if(A[i]<B[j])
        {
            v[k] = A[i];
            i++;
        }
        else
        {
            v[k] = B[j];
            j++;
        }
        k++;
    }
    while(i<x)//
    {
        v[k] = A[i];
        i++;
        k++;
    }
    while(j<y)
    {
        v[k] = B[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int>&v,int st,int dr) //functie recursiva care imparte vectorul in jumatate iar cand ajunge la un singur element
{                                           //lipeste bucatile sortandu-le crescator
    int mij;
    if(st<dr)
    {
        mij = (st+dr)/2;
        MergeSort(v,st,mij);//prima jum
        MergeSort(v,mij+1,dr);//a doua jum
        Merge(v,st,mij,dr);//combinarea celor 2 jum sortand crescator
    }
}

//ShellSort--O(n*logn)
void ShellSort(vector<int>&v,int n)
{
    auto start2 = high_resolution_clock::now();
    int inv,aux,i,j,z;
    for(inv = n/2; inv>0; inv = inv/2)
    {
        for(i = inv;i<n;i++)
        {
            aux = v[i];
            for(j=i;j>=inv && v[j-inv]>aux;j-=inv)
            {
                v[j]=v[j-inv];
            }
            v[j]=aux;
        }
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds> (stop2 - start2);
    int ok=sortat(v,n);
    if(ok==1){cout<<"ShellSort a sortat corect. "<<"Timpul de rulare: "<<duration2.count()<<" microsecunde\n";}
    else{cout<<"ShellSort nu a sortat corect.\n";}
}

//QuickSort1--aleg pivot ultimul element din vector--O(n*logn)

int aranjare(vector<int>&v,int st,int dr)
{
    int pivot,i,j;
    pivot = v[dr];
    i = st-1;
    for(j=st;j<dr;j++)
    {
        if(v[j]<=pivot)
        {
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[dr]);
    i++;
    return i;
}

void  QuickSort1(vector<int>&v,int st,int dr)
{
    int p;
    if(st<dr)
    {
        p = aranjare(v,st,dr);
        QuickSort1(v,st,p-1);
        QuickSort1(v,p+1,dr);
    }
}

//QuickSort2--pivot mediana 3

int mediana(vector<int>&v,int st,int dr)
{
    int mij,pivot,i,j,z;
    mij = (st+dr)/2;
    if(v[st]<=v[dr]&&v[dr]<v[mij]){swap(v[mij],v[dr]);}
    else if(v[mij]<v[st]&&v[st]<v[dr]){swap(v[mij],v[st]);}
    else if(v[dr]<v[st]&&v[st]<=v[mij]){swap(v[dr],v[st]);
                                       swap(v[dr],v[mij]);}
    else if(v[mij]<v[dr]&&v[dr]<=v[st]){swap(v[mij],v[st]);
                                       swap(v[mij],v[dr]);}
    else if(v[dr]<=v[mij]&&v[mij]<v[st]){swap(v[st],v[dr]);}
    pivot = v[mij];
    if(dr-st==1)
    {
        if(v[st]>v[dr]){swap(v[st],v[dr]);}
        i = st+1;
        return i;
    }
    swap(v[mij],v[dr-1]);
    j = dr-1;
    for(i=st+1;i<dr-1;i++)
    {
        if(v[i]>=pivot)
        {
            do{
                j--;
            }
            while(v[j]>=pivot);
            if(i<=j)
            {
                swap(v[i],v[j]);
            }
            else{swap(v[i],v[dr-1]);
                 break;}
        }
    }
    return i;

}

void QuickSort2(vector<int>&v,int st,int dr)
{
    int p;
    if(st<dr)
    {
        p = mediana(v,st,dr);
        QuickSort2(v,st,p-1);
        QuickSort2(v,p+1,dr);
    }
}

//HeapSort--O(n*logn)

void heapify(vector<int>&v,int n,int nod)
{
    int mx,st,dr;
    mx = nod;
    st = 2*nod+1;
    dr = 2*nod+2;

    if(st<n && v[st]>v[mx])
    {
        mx = st;
    }
    if(dr<n && v[dr]>v[mx])
    {
        mx = dr;
    }
    if(mx!=nod)
    {
        swap(v[mx],v[nod]);
        heapify(v,n,mx);
    }
}

void HeapSort(vector<int>&v,int n)
{
    auto start5 = high_resolution_clock::now();
    int i;
    for(i=n/2-1;i>=0;i--)//Max Heap
    {
        heapify(v,n,i);
    }
    for(i=n-1;i>=0;i--)//sortarea
    {
        swap(v[0],v[i]);
        heapify(v,i,0);
    }
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds> (stop5 - start5);
    int ok=sortat(v,n);
    if(ok==1){cout<<"HeapSort a sortat corect. "<<"Timpul de rulare: "<<duration5.count()<<" microsecunde\n";}
    else{cout<<"HeapSort nu a sortat corect.\n";}
}


int main()
{
    ifstream f("fisier.txt");
    int n, mx,t,st,dr,q,i;
    vector<int> a;
    vector<int> v;
    f>>t;

    for(q=1;q<=t;q++)
    {
        f>>n>>mx;
        cout<<n<<" "<<mx<<"\n";
        cout<<"Test "<<q<<":\n";
        random(a,n,mx);
        if(n>100000){cout<<"RadixSort-prea mare"<<endl;}
        else
        {
            v.clear();
            for( i=0;i<n;i++) {
                v.push_back(a[i]);
            }
            RadixSort(v,n);
        }

        if(n>100000){cout<<"MergeSort-prea mare"<<endl;}
        else
        {
            v.clear();
            for(i=0;i<n;i++)
            {
                v.push_back(a[i]);
            }
            auto start1 = high_resolution_clock::now();
            st=0;
            dr=n-1;
            MergeSort(v,st,dr);
            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<microseconds> (stop1 - start1);
            int ok=sortat(v,n);
            if(ok==1){cout<<"MergeSort a sortat corect. "<<"Timpul de rulare: "<<duration1.count()<<" microsecunde\n";}
            else{cout<<"MergeSort nu a sortat corect.\n";}

        }
        if(n>10000000){cout<<"ShellSort-prea mare"<<endl;}
        else
        {
            v.clear();
            for(i=0;i<n;i++)
            {
                v.push_back(a[i]);
            }
            ShellSort(v,n);
        }
        if(n>100000){cout<<"QuickSort1-prea mare"<<endl;}
        else
        {
            v.clear();
            for(i=0;i<n;i++)
            {
                v.push_back(a[i]);
            }
            auto start3 = high_resolution_clock::now();
            st=0;
            dr=n-1;
            QuickSort1(v,st,dr);
            auto stop3 = high_resolution_clock::now();
            auto duration3 = duration_cast<microseconds>(stop3 - start3);
            int ok=sortat(v,n);
            if(ok==1){cout<<"QuickSort cu pivot ultimul element a sortat corect. "<<"Timpul de rulare: "<<duration3.count()<<" microsecunde\n";}
            else{cout<<"QuickSort cu pivot ultimul element nu a sortat corect.\n";}

        }
        if(n>100000){cout<<"QuickSort2-prea mare"<<endl;}
        else
        {
            v.clear();
            for(i=0;i<n;i++)
            {
                v.push_back(a[i]);
            }
            auto start4 = high_resolution_clock::now();
            st=0;
            dr=n-1;
            QuickSort2(v,st,dr);
            auto stop4 = high_resolution_clock::now();
            auto duration4 = duration_cast<microseconds>(stop4 - start4);
            int ok=sortat(v,n);
            if(ok==1){cout<<"QuickSort cu pivot mediana 3 a sortat corect. "<<"Timpul de rulare: "<<duration4.count()<<" microsecunde\n";}
            else{cout<<"QuickSort cu pivot mediana 3 nu a sortat corect.\n";}
        }
        if(n>10000000){cout<<"HeapSort-prea mare"<<endl;}
        else
        {
            v.clear();
            for(i=0;i<n;i++)
            {
                v.push_back(a[i]);
            }
            HeapSort(v,n);
        }
        if(n>100000000){cout<<"Algoritmul nativ c++-prea mare"<<endl;}
        else
        {
            v.clear();
            for(i=0;i<n;i++)
            {
                v.push_back(a[i]);
            }
            auto start6 = high_resolution_clock::now();
            sort(v.begin(), v.end());
            auto stop6 = high_resolution_clock::now();
            auto duration6 = duration_cast<microseconds>(stop6 - start6);
            int ok=sortat(v,n);
            if(ok==1){cout<<"Algoritmul nativ c++ a sortat corect. "<<"Timpul de rulare: "<<duration6.count()<<" microsecunde\n";}
            else{cout<<"Algoritmul nativ c++ nu a sortat corect.\n";}
        }

        a.clear();
        v.clear();
    }
    return 0;
}
