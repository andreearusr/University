
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {

	public:
		string atom;
		int val;
		Node* next;

		//cautarea unui nod in lista inlantuita
		int search(Node* head, string at)
		{
			Node* current = head;
			while (current != NULL) {
				if (current->atom == at)
					return current->val;
				current = current->next;
			}
			return 0;
		}

		//creare nod
		Node* newNode(string at, int value)
		{
			Node* new_node = new Node();
			new_node->atom = at;
			new_node->val = value;
			new_node->next = NULL;

			return new_node;
		}

		//inserare sortata a unui nod in lista inlantuita
		void sortedInsert(Node** head_ref, Node* new_node)
		{
			Node* current;
			/* Special case for the head end */
			if (*head_ref == NULL || (*head_ref)->atom >= new_node->atom) {
				new_node->next = *head_ref;
				*head_ref = new_node;
			}
			else {
				/* Locate the node before the point of insertion */
				current = *head_ref;
				while (current->next != NULL && current->next->atom < new_node->atom) {
					current = current->next;
				}
				new_node->next = current->next;
				current->next = new_node;
			}
		}

		//numarul elementelor din lista inlantuita
		int getCount(Node* head)
		{
			int count = 0;
			Node* current = head;
			while (current != NULL) {
				count++;
				current = current->next;
			}
			return count;
		}

		//adaugare un identificator in TS
		int addTSidentif(string atom, Node** TSidentif, int count) {
			Node* new_node = newNode(atom, count + 1);
			sortedInsert(TSidentif, new_node);
			return new_node->val;
		}

		//adaugare o constanta in TS
		int addTSconst(string atom, Node** TSconst, int count) {
			Node* new_node = newNode(atom, count + 1);
			sortedInsert(TSconst, new_node);
			return new_node->val;
		}

		//scrierea in fisier pentru o anumita TS
		void writeToFileTS(ofstream& fileName, Node* node) {
			int count = 0;
			Node* current = node;
			while (current != NULL) {
				if (current->next != NULL)
					fileName << current->val << " " << current->atom << " " << current->next->val << endl;
				else
					fileName << current->val << " " << current->atom << " " << "-1" << endl;;
				current = current->next;
				count++;
			}
		}

		//printarea listei inlantuite
		void printList(Node* head)
		{
			Node* temp = head;
			while (temp != NULL) {
				cout << temp->atom << " " << temp->val << endl;
				temp = temp->next;
			}
		}
};