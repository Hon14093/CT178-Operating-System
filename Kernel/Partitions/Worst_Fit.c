#include <stdio.h>
#include <limits.h>

int maximum(int bestFit[], int parSize) {
	int i, max=INT_MIN;
	// gan max = gia tri max cua integer
	for (i=1; i<parSize; i++)
		if (bestFit[i] > max && bestFit[i] != -1)
			max = bestFit[i];
	// tim gia tri nho nhat nhung lon hon -1
	// neu khong tim duoc gia tri nho nhat thi tra ve INT_MAX
	return max;
}

void Best_Fit(int phanVung[], int tienTrinh[], int parSize, int proSize) {
	int i, j, parID[6], check[6], tmp[6];
	int bestFit[6], id, max;

    for (j=0; j<parSize; j++)
        tmp[j] = phanVung[j];
	// gan cac phan tu cua mang phanVung vao mang tmp
	// cap nhat lai mang tmp sau moi lan duyet
	// mang tmp chi dung de printf
        
	for (i=0; i<proSize; i++) {
        check[i] = 0; // gan gia tri 0 de tim tien trinh nao chua duoc allocated
		printf("%d: ", i+1); // print thu tu cua moi lan duyet
		
		for (j=0; j<parSize; j++)
		    bestFit[j] = -1;
		// reset lai mang bestFit
		// gan gia tri -1 vao tat ca cac phan tu cua mang

		for (j=0; j<parSize; j++)   
			if (tienTrinh[i] <= phanVung[j])
			    bestFit[j] = phanVung[j];
		// gan lai cac gia tri cua phanVung >= tienTrinh vao mang bestFit
		
        max = maximum(bestFit, parSize);
		for (j=0; j<parSize; j++) {
            if (tienTrinh[i] <= phanVung[j] && phanVung[j] == max) {
                phanVung[j] -= tienTrinh[i];
                printf("%d --%d--> %d => %d is allocated to partition No.%d\n", tmp[j], tienTrinh[i], phanVung[j], tienTrinh[i], j+1);
				check[i] = 1; // neu tienTrinh duoc duyet thi gan check = 1
				break;        // va break khoi vong lap
            }
        }
		
        if (!check[i])
            printf("%d is not allocated\n", tienTrinh[i]);
	}
}

void printPartitionID(int phanVung[], int parSize) {
    int i;
    printf("|-----|-------------|\n");
    printf("| No. |  Paritions  |\n");
    printf("|-----|-------------|\n");
    for (i=0; i<parSize; i++)
        printf("|  %d  |     %d     |\n", i+1, phanVung[i]);
    printf("|-----|-------------|\n");
    printf("\n");
}

void printParAfter(int phanVung[], int parSize) {
    int i;
    printf("\n\nCac kich thuoc phan vung sau khi allocate:\n");
    for (i=0; i<parSize; i++)
        printf("%d ", phanVung[i]);
    printf("\n");
}

int main() {
	int phanVung[] = {300, 600, 350, 200, 750, 125};
	int tienTrinh[] = {115, 500, 358, 200, 375, 1300};
	int parSize = sizeof(phanVung) / sizeof(phanVung[0]); // Lay size cua mang phanVung
	int proSize = sizeof(tienTrinh) / sizeof(tienTrinh[0]); // Lay size cua mang tienTrinh
	
	printPartitionID(phanVung, parSize); // print ID cua cac phan vung
	Best_Fit(phanVung, tienTrinh, parSize, proSize);
	printParAfter(phanVung, parSize); // print kich thuoc cac phan vung sau khi cap phat
}

// cac phan vung co kich thuoc la:
// 300, 600, 350, 200, 750, 125
// cac tien trinh co kich thuoc la:
// 115, 500, 358, 200, 375, 1300

// Output:
// |-----|-------------|
// | No. |  Paritions  |
// |-----|-------------|
// |  1  |     300     |
// |  2  |     600     |
// |  3  |     350     |
// |  4  |     200     |
// |  5  |     750     |
// |  6  |     125     |
// |-----|-------------|

// 1: 750 --115--> 635 - 115 is allocated to partition No.5
// 2: 635 --500--> 135 - 500 is allocated to partition No.5
// 3: 600 --358--> 242 - 358 is allocated to partition No.2
// 4: 350 --200--> 150 - 200 is allocated to partition No.3
// 5: 375 is not allocated
// 6: 1300 is not allocated

// Cac kich thuoc phan vung sau khi allocate:
// 300 242 150 200 135 125

// Idea:
// - Tao mang bestFit va gan cac gia tri cua no = -1
// - muc dich cua mang bestFit la de luu nhung phan vung ma tien trinh x co the duoc cap vao
// - max = gia tri lon nhat trong mang bestFit