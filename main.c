#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char *kelime;
    int *adet;
    struct node *next;

};

struct node* start = NULL;
struct node* q = NULL;
struct node* p = NULL;
int sayac=0;


void sonaEkle(char *kelime,int adet){

    struct node* eklenecek =(struct node*)malloc(sizeof(struct node));
    eklenecek->kelime =(char*)malloc(1000*sizeof(char));

    strcpy(eklenecek->kelime,kelime);
    eklenecek->adet = adet;
    eklenecek->next = NULL;

    if(start ==NULL){
        start = eklenecek;
    }

    else{
        q= start;

        while(q->next!=NULL){
            q=q->next;
        }
        q->next = eklenecek;
    }

}


void arayaEkle(int sonraki,char *kelime,int adet){

    struct node* arayaEklenecek =(struct node*)malloc(sizeof(struct node));
    arayaEklenecek->kelime =(char*)malloc(1000*sizeof(char));

    strcpy(arayaEklenecek->kelime,kelime);
    arayaEklenecek->adet = adet;
    q=start;

    while(q->next->adet!=sonraki){
        q=q->next;
    }

    struct node* onune =(struct node*)malloc(sizeof(struct node));

    onune=q->next;
    q->next=arayaEklenecek;
    arayaEklenecek->next=onune;
}

void basaEkle(char *kelime,int adet){

    struct node* basaEklenecek =(struct node*)malloc(sizeof(struct node));
    basaEklenecek->kelime =(char*)malloc(1000*sizeof(char));

    strcpy(basaEklenecek->kelime,kelime);

    basaEklenecek->next = start;
    basaEklenecek->adet = adet;
    start=basaEklenecek;
}


void listeyeEkle(char *kelime,int adet){

    int say=0;

    if(start ==NULL){
    //Listede hiç eleman yoksa burasý çalýþacak.
        sonaEkle(kelime,adet);
        say++;
    }

    else{
        q=start;
        p=start;

        while(q != NULL){
            if(adet >= q->adet){
                if(q->adet== p->adet){
                    basaEkle(kelime,adet);
                    say++;
                    break;
            }
            else{
                    int k= q->adet;
                    arayaEkle(k,kelime,adet);
                    say++;
                    break;
                }
            }

            q=q->next;
        }

        if(say==0){
            sonaEkle(kelime,adet);
        }
    }
}

void kelimeAl(char *cumle)
{
  char kontrol[1000];
    char kontrol2[1000];
    char kelime[100];

    int y=0;
    while(y<100){
        kelime[y]=NULL;
        y++;
    }

    int b = 0,baslangic=0,bitis=0;

    for(int i =0; i<10000; i++)
    {

        if(cumle[i]==' ' || cumle[i]==NULL){

            bitis=i-1;

            int j=0;

            for(int i2 =baslangic; i2<=bitis; i2++){

                kelime[j]=cumle[i2];
                j++;
            }
            // sayilacak kelime bulundu.
            char cumle2[1000];

            for(int k=0; k<1000; k++)
            {

                if( cumle[k]==NULL)
                    break;

                cumle2[k]=cumle[k];
            }

            //cumleyi kopyaladik ve kopyasni foksiyona yolladik.

            ///////////////////////////////////////////////////////////////////////////////

             if(start !=NULL){

                q=start;

                while(q != NULL){

                   int ret = strcmp(kelime,q->kelime);



                    if(ret==0)
                    {
                        b=1;
                    }

                    q=q->next;
                }
            }

            /////////////////////////////////////////////////////////////////////////////

            if(b==0){
                say(cumle2,kelime);
            }

            b=0;

            baslangic = bitis+2;

            for(int i=0; i<100; i++)
            {
                kelime[i]=NULL;
            }

            if( cumle[i]==NULL)
                break;

        }

    }

}


void say(char *cumle2,char *kelime){
    char kontrolKelime[100];
    int ret;
    int baslangic=0,bitis=0;

    for(int i =baslangic; i<10000; i++){

        if(cumle2[i]==' ' || cumle2[i]==NULL){

            int j=0;
            bitis=i-1;

            for(int i =baslangic; i<=bitis; i++){
                kontrolKelime[j]=cumle2[i];
                j++;
            }
            ret = strcmp(kelime,kontrolKelime);
            if(ret==0){
                sayac+=1;

            }

            baslangic = bitis+2;

            for(int i=0; i<100; i++){
                kontrolKelime[i]=NULL;
            }

            if( cumle2[i]==NULL){
                break;
            }
        }
    }

    listeyeEkle(kelime,sayac);
    sayac=0;

}

void yazdir(){
    q=start;
    int i=1;

    while(q != NULL){
        printf("%2d. | %s : %d\n",i,q->kelime,q->adet);
        q=q->next;
        i++;
    }

}

int main(){
    FILE *dosya = fopen("metin.txt","r");

    char cumle[10000]={0};


   if(dosya == NULL)
   {
      printf("\n      Hata, Dosya bulunamadi !!!!\n");
      exit(1);
   }

    fgets( cumle, feof, dosya );

    printf("\n%s\n",cumle);

    kelimeAl(cumle);

    printf("\n---------------------------------\n");
    yazdir();
    printf("---------------------------------\n");

    fclose(dosya);

    return 0;
}
