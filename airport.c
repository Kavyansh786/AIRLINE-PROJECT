#include <stdio.h>
#include <stdlib.h>
struct passenger
{
    int seat_number;
    char gen;
    int age;
    char classs[10];
    char name[20];
};
int comp(struct passenger A, struct passenger B)
{
    // For age
    if (A.age >= 60 && B.age >= 60)
    {
        if (A.classs == B.classs)
        {
            if (A.seat_number < B.seat_number)
                return 1;
            else
                return 2;
        }
        else
        {
            if (A.classs[0] == 'f')
                return 1;
            else
                return 2;
        }
    }
    else if (A.age >= 60 || B.age >= 60)
    {
        if (A.age >= 60)
            return 1;
        else
            return 2;
    }
    // For gender
    if (A.gen == 'F' && B.gen == 'F')
    {
        if (A.classs == B.classs)
        {
            if (A.seat_number < B.seat_number)
                return 1;
            else
                return 2;
        }
        else
        {
            if (A.classs[0] == 'f')
                return 1;
            else
                return 2;
        }
    }
    else if (A.gen == 'F' || B.gen == 'F')
    {
        if (A.gen == 'F')
            return 1;
        else
            return 2;
    }
    // For class and seat number
    if (A.classs == B.classs)
    {
        if (A.seat_number < B.seat_number)
            return 1;
        else
            return 2;
    }
    else
    {
        if (A.classs[0] == 'f')
            return 1;
        else
            return 2;
    }
    return 0;
}
void merge(struct passenger arr[], int l, int mid, int r)
{
    struct passenger temp[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (comp(arr[i], arr[j]) == 1)
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];

    for (int i = 0; i < r - l + 1; i++)
    {
        arr[i + l] = temp[i];
    }
}
void merge_sort(struct passenger arr[], int l, int r)
{
    if (l<r)
      {
    int mid = (l + r) / 2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    merge(arr, l, mid, r);
      }
}
int main()
{
    struct passenger passengers[100];
    int num_passengers = 0;
    FILE *file = fopen("traveler_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    // Read passenger details from file
    while (fscanf(file, "%d %c %d %s %s\n", &passengers[num_passengers].seat_number,
                  &passengers[num_passengers].gen, &passengers[num_passengers].age,
                  passengers[num_passengers].classs, passengers[num_passengers].name) != EOF)
    {
        num_passengers++;
    }
    fclose(file);
    struct passenger gate1[100],gate2[100];
    int front1=0,front2=0,rear1=-1,rear2=-1;
    for(int i=0;i<num_passengers;i++)
    {
        if(passengers[i].gen=='F'||passengers[i].age>=60)
            gate1[++rear1]=passengers[i];
        else
            gate2[++rear2]=passengers[i];
    }
    // Perform merge sort on the passengers array
    merge_sort(gate1, 0, rear1);
    merge_sort(gate2,0,rear2);
    printf("TOTAL PASSENGERS=%d\n",num_passengers);
    printf("BOARDING PROCESS HAS STARTED:\n");
    int flag=0;
    while(front1<=rear1||front2<=rear2)
    {
        if(front1>rear1)
            flag=1;
        if(front1<=rear1)
        {
            printf(" Name:%s\tClass:%s\tSeat: %d \tGate No.:1\n ",
                   gate1[front1].name, gate1[front1].classs, gate1[front1].seat_number);
                   front1++;
        }
         if(front2<=rear2)
        {
            printf("Name:%s\tClass:%s\tSeat: %d \tGate No.:2\n",
                   gate2[front2].name, gate2[front2].classs, gate2[front2].seat_number);
            front2++;
            if (flag==1 && front2<=rear2)
        {
            printf("THIS PERSON IS BEING UPGRADED Name:%s\tClass:%s\tSeat: %d \tGate No.:1\n",
                   gate2[front2].name, gate2[front2].classs, gate2[front2].seat_number);
            front2++;
        }
        }
    }
    return 0;
}
