#include "your_reduce.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <sstream>

void YOUR_Reduce(const int *sendbuf, int *recvbuf, int count)
{
    /*
        Modify the code here.
        Your implementation should have the same result as this MPI_Reduce
        call. However, you MUST NOT use MPI_Reduce (or like) for your hand-in
        version. Instead, you should use MPI_Send and MPI_Recv (or like). See
        the homework instructions for more information.
    */
    // MPI_Reduce(sendbuf, recvbuf, count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    /*
        You may assume:
        - Data type is always `int` (MPI_INT).
        - Operation is always MPI_SUM.
        - Process to hold final results is always process 0.
        - Number of processes is 2, 4, or 8.
        - Number of elements (`count`) is 1, 16, 256, 4096, 65536, 1048576,
          16777216, or 268435456.
        For other cases, your code is allowed to produce wrong results or even
        crash. It is totally fine.
    */
    int thisProc, nProc;
    MPI_Comm_rank(MPI_COMM_WORLD, &thisProc);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Status status;

    int dest;
    int width;
    
    // Copy original data so that sendbuf is not modified
    int *myData = new int[count];
    for (int i = 0; i < count; i++)
        myData[i] = sendbuf[i];

    // create a temp buf for manipulation
    int *temp_sendbuf = new int[count];
    for (int i = 0; i < count; i++)
        temp_sendbuf[i] = sendbuf[i];

    int nPhases = log2(nProc);

    for (int p = 0; p < nPhases; p++)
    {
        // the size of the message
        width = (count / pow(2, p + 1));

        if (thisProc % ((int)pow(2, p + 1)) < (int)pow(2, p + 1) / 2)
        {
            dest = thisProc + pow(2, p);
            for (int i = 0; i < width; i++)
                temp_sendbuf[i] = myData[i + width]; // second half of the message

            MPI_Send(temp_sendbuf, width, MPI_INT, dest, 0, MPI_COMM_WORLD);
            MPI_Recv(recvbuf, width, MPI_INT, dest, 1, MPI_COMM_WORLD, &status);

            for (size_t i = 0; i < width; i++)
                myData[i] += recvbuf[i]; // sum the replay
        }
        else
        {
            dest = thisProc - pow(2, p);

            MPI_Recv(recvbuf, width, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);

            for (int i = 0; i < width; i++)
                temp_sendbuf[i] = myData[i]; // first half of the message

            for (size_t i = 0; i < width; i++)
                myData[i + width] += recvbuf[i]; // sum the replay
            MPI_Send(temp_sendbuf, width, MPI_INT, dest, 1, MPI_COMM_WORLD);

            // Copy the second half on the first half
            for (size_t i = 0; i < width; i++)
                myData[i] = myData[i + width];
        }
    }
    // for each process
    for (int p = nPhases - 1; p >= 0; p--)
    {
        width = (count / pow(2, p + 1));
        if (thisProc % ((int)pow(2, p + 1)) < (int)pow(2, p + 1) / 2)
        {
            dest = thisProc + pow(2, p);
            for (int i = 0; i < width; i++)
                temp_sendbuf[i] = myData[i];
            MPI_Send(temp_sendbuf, width, MPI_INT, dest, 0, MPI_COMM_WORLD);
            MPI_Recv(recvbuf, width, MPI_INT, dest, 1, MPI_COMM_WORLD, &status);

            for (size_t i = 0; i < width; i++)
                myData[i + width] = recvbuf[i];
        }
        else
        {
            dest = thisProc - pow(2, p);

            MPI_Recv(recvbuf, width, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);

            for (int i = 0; i < width; i++)
                temp_sendbuf[i] = myData[i];

            for (size_t i = 0; i < width; i++)
                myData[i + width] = myData[i];

            for (size_t i = 0; i < width; i++)
                myData[i] = recvbuf[i];
            MPI_Send(temp_sendbuf, width, MPI_INT, dest, 1, MPI_COMM_WORLD);
        }
    }
    // copy output to recvbuffer
    for (size_t i = 0; i < count; i++)
        recvbuf[i] = myData[i];
    // clear temporary storage
    delete[] myData;
    delete[] temp_sendbuf;
}
