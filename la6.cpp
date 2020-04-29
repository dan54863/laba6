#include <fstream>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <pthread.h>
using namespace std;
void * thread_func(void *);
static pthread_barrier_t bar;
static pthread_mutex_t m;
int main()
{
    setlocale(LC_ALL, "rus");
	string s;
	int i=0,j=0; 
	int k,t=-1;
    int q=0;
    int status;
    pthread_mutex_init(&m, NULL);
    pthread_barrier_t bar;
	ifstream ifs ("/home/danil/123.txt");
    while(getline(ifs, s))
    {
        ++q;
    }
    pthread_t tid[q]; //thread array
    string s_a[q];
    ifs.close();
    pthread_barrier_init(&bar, NULL, q);
    ifstream ifs1 ("/home/danil/123.txt");
    for(i=0; i<q; ++i)
    {
        getline(ifs1, s_a[i]);
    }
	for(i=0; i<q; ++i)
	{
		status=pthread_create(&tid[i], NULL, thread_func, (void *)&s_a[i]);
        if(status!=0)
            cout << "It doesn't work!\n";
	}
    void *a=NULL;
    string *b=NULL;
    for(i=0; i<q; ++i)
    {
        pthread_join(tid[i], &a);
        b=(string *)a;
        if(*b=="0")
            ++j;
    }
    cout<< j << endl;
    pthread_barrier_destroy(&bar);
    pthread_mutex_destroy(&m);
	ifs1.close();
	return (0);
}

void * thread_func(void *s)
{
    pthread_mutex_lock(&m);
    setlocale(LC_ALL, "Russian");
    string *s1=(string *)s;
    cout << *s1 << endl;
    string s12 = "витамин";
    cout << "Что ищем: " << s12 << endl << endl;
    //pthread_barrier_wait(&bar);
    if (s1->find(s12)<=s1->length())
    {
        cout << "подстрока входит\n\n";
        s1[0]='0';
        pthread_mutex_unlock(&m);
        return (s);
    }
    else
    {
        cout << "подстрока Не входит\n\n";
        s1[0]='1';
        pthread_mutex_unlock(&m);
        return (s);
    }
}
