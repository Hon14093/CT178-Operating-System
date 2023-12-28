#include <stdio.h>

void First_Fit(int phanVung[], int tienTrinh[], int parSize, int proSize) {
	int i, j, check[proSize], tmp[parSize];

	for (i=0; i<parSize; i++) 
	    tmp[i] = phanVung[i];
	// gan cac phan tu cua mang phanVung vao mang tmp
	// cap nhat lai mang tmp sau moi lan duyet
	// mang tmp chi dung de printf
	
	for (i=0; i<proSize; i++) {
		check[i] = 0; // gan gia tri 0 de tim tien trinh nao chua duoc allocated
		printf("%d: ", i+1); // print thu tu cua moi lan duyet
		
		for (j=0; j<parSize; j++) {
			if (tienTrinh[i] <= phanVung[j]) {
				phanVung[j] -= tienTrinh[i]; // lay phanVung - tienTrinh
				printf("%d --%d--> %d => %d is allocated to partition No.%d", tmp[j], tienTrinh[i], phanVung[j], tienTrinh[i], j+1);
				check[i] = 1; // neu tienTrinh duoc duyet thi gan check = 1
				break;        // va break khoi vong lap
			}
		}
		// neu tienTrinh[i] van bang 0 sau khi duyet qua cac partitions thi thong bao chua duoc allocated
		if (!check[i])
		    printf("%d is not allocated", tienTrinh[i]);
		printf("\n");
	}
}

void printPartitionID(int phanVung[], int parSize) {
    int i;
    printf("|-----|-------------|\n");
    printf("| No. |\t Paritions  |\n");
    printf("|-----|-------------|\n");
    for (i=0; i<parSize; i++)
        printf("|  %d  |\t    %d     |\n", i+1, phanVung[i]);
    printf("|-----|-------------|\n");
    printf("\n");
}

void printParAfter(int phanVung[], int parSize) {
    int i;
    printf("\nCac kich thuoc phan vung sau khi allocate:\n");
    for (i=0; i<parSize; i++)
        printf("%d ", phanVung[i]);
}

int main() {
	int phanVung[] = {300, 600, 350, 200, 750, 125};
	int tienTrinh[] = {115, 500, 358, 200, 375, 1300};
	int parSize = sizeof(phanVung) / sizeof(phanVung[0]); // Lay size cua mang phanVung
	int proSize = sizeof(tienTrinh) / sizeof(tienTrinh[0]); // Lay size cua mang tienTrinh
	
	printPartitionID(phanVung, parSize); // print ID cua cac phan vung
	First_Fit(phanVung, tienTrinh, parSize, proSize);
	printParAfter(phanVung, parSize);
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

// 1: 300 --115--> 185 - 115 is allocated to partition No.1
// 2: 600 --500--> 100 - 500 is allocated to partition No.2
// 3: 750 --358--> 392 - 375 is allocated to partition No.5
// 4: 350 --200--> 150 - 358 is allocated to partition No.3
// 5: 392 --375--> 17 - 375 is allocated to partition No.5
// 6: 1300 not allocated

// Cac kich thuoc phan vung sau khi allocate:
// 185 100 150 200 17 125 