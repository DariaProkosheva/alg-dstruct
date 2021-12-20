#include "gtest/gtest.h"
extern "C"
{
#include "D.h"
}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST(ListPush, Node_Pushed) {
	node* list = (node*)malloc(sizeof(node));
	list->wag = 1;
	list->next = NULL;
	node**  p = &(list);
	ListPush(p, 6);
	EXPECT_TRUE((*p)->wag == 6);
	EXPECT_TRUE((*p)->next->wag == 1);
	EXPECT_TRUE((*p)->next->next == NULL);
}

TEST(WagComposition, Test1_NoTime) {
	const unsigned WW = 5;
	unsigned DD = 0;
	unsigned KK = 2;
	unsigned NN = 3;
	unsigned wags[WW] = { 1, 2, 3, 4, 5 };
	unsigned time[WW] = {2, 2, 3, 3, 1};
	FILE* fileinput1 = fopen("fileinput1.txt", "w");
	fprintf(fileinput1, "%d %d %d\n", WW, DD, KK);
	for (int i = 0; i < WW; i++)
		fprintf(fileinput1, "%d ", time[i]);
	fprintf(fileinput1, "\n");
	fprintf(fileinput1, "%d\n", NN);
	fprintf(fileinput1, "%d %d\n", wags[3], wags[2]);
	fprintf(fileinput1, "%d %d\n", wags[4], wags[2]);
	fprintf(fileinput1, "%d %d\n", wags[4], wags[1]);
	fclose(fileinput1);
	WagComposition("fileinput1.txt", "fileoutput1.txt");
	FILE* f = fopen("fileoutput1.txt", "r");
	int p;
	fscanf(f, "%d", &p);
	EXPECT_TRUE(p == 0);
}
TEST(WagComposition, Test2_WagMin) {
	const unsigned WW = 3;
	unsigned DD = 10;
	unsigned KK = 1;
	unsigned NN = 1;
	unsigned wags[3] = { 1, 2, 3 };
	unsigned time[3] = { 5, 3, 4 };
	FILE* fileinput1 = fopen("fileinput2.txt", "w");
	fprintf(fileinput1, "%d %d %d\n", WW, DD, KK);
	for (int i = 0; i < 3; i++)
		fprintf(fileinput1, "%d ", time[i]);
	fprintf(fileinput1, "\n");
	fprintf(fileinput1, "%d\n", NN);
	fprintf(fileinput1, "%d %d\n", wags[2], wags[1]);
	fclose(fileinput1);
	WagComposition("fileinput2.txt", "fileoutput2.txt");
	FILE* f = fopen("fileoutput2.txt", "r");
	int p,  k;
	fscanf(f, "%d %d", &p, &k);
	EXPECT_TRUE(p != 0);
	EXPECT_TRUE(p == 3);
	EXPECT_TRUE(k == 2);
}
TEST(WagComposition, Test3_NoWagonsLeft) {
	const unsigned WW = 5;
	unsigned DD = 30;
	unsigned KK = 0;
	unsigned NN = 3;
	unsigned wags[5] = { 1, 2, 3, 4, 5 };
	unsigned time[5] = { 2, 2, 3, 3, 1 };
	FILE* fileinput1 = fopen("fileinput3.txt", "w");
	fprintf(fileinput1, "%d %d %d\n", WW, DD, KK);
	for (int i = 0; i < 5; i++)
		fprintf(fileinput1, "%d ", time[i]);
	fprintf(fileinput1, "\n");
	fprintf(fileinput1, "%d\n", NN);
	fprintf(fileinput1, "%d %d\n", wags[3], wags[2]);
	fprintf(fileinput1, "%d %d\n", wags[4], wags[2]);
	fprintf(fileinput1, "%d %d\n", wags[4], wags[1]);
	fclose(fileinput1);
	WagComposition("fileinput3.txt", "fileoutput3.txt");
	FILE* f = fopen("fileoutput3.txt", "r");
	int p;
	fscanf(f, "%d", &p);
	EXPECT_TRUE(p != 0);
}
TEST(WagComposition, Test4_TroublePairs) {
	const unsigned WW = 4;
	unsigned DD = 100;
	unsigned KK = 0;
	unsigned NN = 2;
	unsigned wags[WW] = { 1, 2, 3, 4 };
	unsigned time[WW] = { 3, 3, 3, 3 };
	FILE* fileinput1 = fopen("fileinput4.txt", "w");
	fprintf(fileinput1, "%d %d %d\n", WW, DD, KK);
	for (int i = 0; i < WW; i++)
		fprintf(fileinput1, "%d ", time[i]);
	fprintf(fileinput1, "\n");
	fprintf(fileinput1, "%d\n", NN);
	fprintf(fileinput1, "%d %d\n", wags[1], wags[3]);
	fprintf(fileinput1, "%d %d\n", wags[3], wags[1]);
	fclose(fileinput1);
	WagComposition("fileinput4.txt", "fileoutput4.txt");
	FILE* f = fopen("fileoutput4.txt", "r");
	int p;
	fscanf(f, "%d", &p);
	EXPECT_TRUE(p == 0);
}
TEST(WagComposition, Test5_Task) {
	const unsigned WW = 10;
	unsigned DD = 40;
	unsigned KK = 3;
	unsigned NN = 4;
	unsigned wags[WW] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	unsigned time[WW] = { 5, 3, 3, 3, 6, 7, 7, 9, 10, 10 };
	FILE* fileinput1 = fopen("fileinput5.txt", "w");
	fprintf(fileinput1, "%d %d %d\n", WW, DD, KK);
	for (int i = 0; i < WW; i++)
		fprintf(fileinput1, "%d ", time[i]);
	fprintf(fileinput1, "\n");
	fprintf(fileinput1, "%d\n", NN);
	fprintf(fileinput1, "%d %d\n", wags[2], wags[1]);
	fprintf(fileinput1, "%d %d\n", wags[3], wags[1]);
	fprintf(fileinput1, "%d %d\n", wags[9], wags[6]);
	fprintf(fileinput1, "%d %d\n", wags[6], wags[8]);
	fclose(fileinput1);
	WagComposition("fileinput5.txt", "fileoutput5.txt");
	FILE* f = fopen("fileoutput5.txt", "r");
	int p;
	int arr[7];
	for (int i=0; i< WW-KK; i++)
	fscanf(f, "%d", &arr[i]);
	EXPECT_TRUE(arr[0] == 1);
	EXPECT_TRUE(arr[1] == 3);
	EXPECT_TRUE(arr[2] == 4);
	EXPECT_TRUE(arr[3] == 2);
	EXPECT_TRUE(arr[4] == 5);
	EXPECT_TRUE(arr[5] == 6);
	EXPECT_TRUE(arr[6] == 7);
}