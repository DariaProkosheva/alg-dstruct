#include "gtest/gtest.h"
extern "C" 
{
#include "A.h"
}
TEST(CreatNode, Data_CorrectNode) {
	Node* node = CreateNode(1);
	EXPECT_TRUE(node != NULL);
	EXPECT_FALSE(node->data == 5);
	ASSERT_TRUE(node->data == 1);
	EXPECT_TRUE(node->next == NULL);
}
TEST(AddNode, Node_Added) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	Node** point = &(list);
	AddNode(point, 5);
	EXPECT_TRUE((*point)->data == 1);
	(*point) = (*point)->next;
	EXPECT_TRUE((*point)->data == 5);
	EXPECT_TRUE((*point)->next == NULL);
}
TEST(AddNode, Node_AddedOrdered) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	Node** point = &(list);
	AddNode(point, 5);
	AddNode(point, 3);
	EXPECT_TRUE((*point)->data == 1);
	(*point) = (*point)->next;
	EXPECT_TRUE((*point)->data == 3);
	(*point) = (*point)->next;
	EXPECT_TRUE((*point)->data == 5);
	EXPECT_TRUE((*point)->next == NULL);
}
TEST(DeleteNode, FirstNode_Deleted) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	Node** point = &(list);
	DeleteNode(point, 1);
	EXPECT_TRUE(*point == NULL);
}
TEST(DeleteNode, SecondNode_Deleted) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	Node* new_list = (Node*)malloc(sizeof(Node));
	new_list->data = 5;
	new_list->next = NULL;
	new_list->next = list->next;
	list->next = new_list;
	Node** point = &(list);
	DeleteNode(point, 5);
	EXPECT_TRUE((*point)->data == 1);
	EXPECT_TRUE((*point)->next == NULL);
}
TEST(DeleteNode, NoNode_Deleted) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	Node* new_list = (Node*)malloc(sizeof(Node));
	new_list->data = 5;
	new_list->next = list->next;
	list->next = new_list;
	Node** point = &(list);
	DeleteNode(point, 6);
	EXPECT_TRUE((*point)->data == 1);
	EXPECT_TRUE((*point)->next->data == 5);
	EXPECT_TRUE((*point)->next->next == NULL);
}
TEST(PushNode, Node_Pushed) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	Node** point = &(list);
	PushNode(point, 6);
	EXPECT_TRUE((*point)->data == 6);
	EXPECT_TRUE((*point)->next->data == 1);
	EXPECT_TRUE((*point)->next->next == NULL);
}
TEST(IsElement, ElementIn) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	int k = IsElement(list, 1);
	EXPECT_TRUE(k == 1);
}
TEST(IsElement, ElementOut) {
	Node* list = (Node*)malloc(sizeof(Node));
	list->data = 1;
	list->next = NULL;
	int d = IsElement(list, 6);
	EXPECT_TRUE(d == 0);
}
TEST(GetNodeIntersection, NodeInter) {
	Node* list1 = (Node*)malloc(sizeof(Node));
	list1->data = 1;
	list1->next = NULL;
	Node* list2 = (Node*)malloc(sizeof(Node));
	list2->data = 2;
	list2->next = NULL;
	list2->next = list1->next;
	list1->next = list2;
	Node* list3 = (Node*)malloc(sizeof(Node));
	list3->data = 3;
	list3->next = NULL;
	list2->next = list3->next;
	list2->next = list3;
	Node* list11 = (Node*)malloc(sizeof(Node));
	list11->data = 1;
	list11->next = NULL;
	Node* list22 = (Node*)malloc(sizeof(Node));
	list22->data = 3;
	list22->next = NULL;
	list22->next = list11->next;
	list11->next = list22;
	Node* list33 = (Node*)malloc(sizeof(Node));
	list33->data = 5;
	list33->next = NULL;
	list22->next = list33->next;
	list22->next = list33;
	Node** point1 = &list1;
	Node** point2 = &list11;
	Node* node_inter = GetNodeIntersection(point1, point2);
	EXPECT_TRUE(node_inter->data == 1);
	EXPECT_TRUE(node_inter->next->data == 3);
	EXPECT_TRUE(node_inter->next->next == NULL);
}
TEST(GetNodeUnion, NodeUnion) {
	Node* list1 = (Node*)malloc(sizeof(Node));
	list1->data = 1;
	list1->next = NULL;
	Node* list2 = (Node*)malloc(sizeof(Node));
	list2->data = 2;
	list2->next = NULL;
	list2->next = list1->next;
	list1->next = list2;
	Node* list3 = (Node*)malloc(sizeof(Node));
	list3->data = 3;
	list3->next = NULL;
	list2->next = list3->next;
	list2->next = list3;
	Node* list11 = (Node*)malloc(sizeof(Node));
	list11->data = 1;
	list11->next = NULL;
	Node* list22 = (Node*)malloc(sizeof(Node));
	list22->data = 3;
	list22->next = NULL;
	list22->next = list11->next;
	list11->next = list22;
	Node* list33 = (Node*)malloc(sizeof(Node));
	list33->data = 5;
	list33->next = NULL;
	list22->next = list33->next;
	list22->next = list33;
	Node** point1 = &list1;
	Node** point2 = &list11;
	Node* node_union = GetNodeUnion(point1, point2);
	EXPECT_TRUE(node_union->data == 1);
	node_union = node_union->next;
	EXPECT_TRUE(node_union->data == 2);
	node_union = node_union->next;
	EXPECT_TRUE(node_union->data == 3);
	node_union = node_union->next;
	EXPECT_TRUE(node_union->data == 5);
	EXPECT_TRUE(node_union->next == NULL);
}
TEST(ReverseNode, NodeReverse) {
	Node* list1 = (Node*)malloc(sizeof(Node));
	list1->data = 1;
	list1->next = NULL;
	Node* list2 = (Node*)malloc(sizeof(Node));
	list2->data = 2;
	list2->next = NULL;
	list2->next = list1->next;
	list1->next = list2;
	Node* list3 = (Node*)malloc(sizeof(Node));
	list3->data = 3;
	list3->next = NULL;
	list2->next = list3->next;
	list2->next = list3;
	Node** point = &(list1);
	ReverseNode(point);
	EXPECT_TRUE((*point)->data == 3);
	(*point) = (*point)->next;
	EXPECT_TRUE((*point)->data == 2);
	(*point) = (*point)->next;
	EXPECT_TRUE((*point)->data == 1);
	EXPECT_TRUE((*point)->next == NULL);
}
