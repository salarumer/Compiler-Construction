// C++ implementation of Symbol Table using the concept of Hashing with separate chaining
#include <iostream> 
using namespace std; 

const int MAX = 100; // Maximum size of the hash table

// Node class to represent each identifier in the symbol table
class Node { 
	string identifier, scope, type; // Information stored for each identifier: name, scope, type
	int lineNo; // Line number where the identifier is declared
	Node* next; // Pointer to the next node in case of collision (separate chaining)

public: 
	Node() { 
		next = NULL; 
	} 

	Node(string key, string value, string type, int lineNo) { 
		this->identifier = key; 
		this->scope = value; 
		this->type = type; 
		this->lineNo = lineNo; 
		next = NULL; 
	} 

	// Function to print information about the identifier
	void print() { 
		cout << "Identifier's Name:" << identifier 
			<< "\nType:" << type 
			<< "\nScope: " << scope 
			<< "\nLine Number: " << lineNo << endl; 
	} 
	friend class SymbolTable; // SymbolTable class is a friend to access private members
}; 

// SymbolTable class to manage the symbol table
class SymbolTable { 
	Node* head[MAX]; // Array of pointers to nodes (hash table)

public: 
	SymbolTable() { 
		for (int i = 0; i < MAX; i++) 
			head[i] = NULL; // Initialize all head pointers to NULL
	} 

	int hashf(string id); // Function prototype for hash function
	bool insert(string id, string scope, string Type, int lineno); // Function prototype for inserting an identifier
	string find(string id); // Function prototype for finding an identifier
	bool deleteRecord(string id); // Function prototype for deleting an identifier
	bool modify(string id, string scope, string Type, int lineno); // Function prototype for modifying an identifier
}; 

// Function to modify an identifier
bool SymbolTable::modify(string id, string s, string t, int l) { 
	int index = hashf(id); 
	Node* start = head[index]; 

	if (start == NULL) 
		return false; // Identifier not found

	while (start != NULL) { 
		if (start->identifier == id) { 
			start->scope = s; 
			start->type = t; 
			start->lineNo = l; 
			return true; // Identifier modified successfully
		} 
		start = start->next; 
	} 

	return false; // Identifier not found 
} 

// Function to delete an identifier
bool SymbolTable::deleteRecord(string id) { 
	int index = hashf(id); 
	Node* tmp = head[index]; 
	Node* par = head[index]; 

	if (tmp == NULL) { // No identifier is present at that index
		return false; 
	} 
	if (tmp->identifier == id && tmp->next == NULL) { // Only one identifier is present
		tmp->next = NULL; 
		delete tmp; 
		return true; // Identifier deleted successfully
	} 

	while (tmp->identifier != id && tmp->next != NULL) { // Search for the identifier
		par = tmp; 
		tmp = tmp->next; 
	} 
	if (tmp->identifier == id && tmp->next != NULL) { // Identifier found in the middle of the chain
		par->next = tmp->next; 
		tmp->next = NULL; 
		delete tmp; 
		return true; // Identifier deleted successfully
	} 

	// Delete at the end
	else { 
		par->next = NULL; 
		tmp->next = NULL; 
		delete tmp; 
		return true; // Identifier deleted successfully
	} 
	return false; 
} 

// Function to find an identifier
string SymbolTable::find(string id) { 
	int index = hashf(id); 
	Node* start = head[index]; 

	if (start == NULL) 
		return "-1"; // Identifier not found

	while (start != NULL) { 
		if (start->identifier == id) { 
			start->print(); // Print information about the identifier
			return start->scope; // Return scope of the identifier
		} 
		start = start->next; 
	} 

	return "-1"; // Identifier not found 
} 

// Function to insert an identifier
bool SymbolTable::insert(string id, string scope, string Type, int lineno) { 
	int index = hashf(id); 
	Node* p = new Node(id, scope, Type, lineno); // Create a new node for the identifier

	if (head[index] == NULL) { // If no identifier exists at this index, insert the new node
		head[index] = p; 
		cout << "\n" << id << " inserted"; // Print message indicating successful insertion
		return true; // Identifier inserted successfully
	} 

	else { 
		Node* start = head[index]; 
		while (start->next != NULL) 
			start = start->next; 

		start->next = p; // Insert at the end of the chain
		cout << "\n" << id << " inserted"; // Print message indicating successful insertion
		return true; // Identifier inserted successfully
	} 

	return false; // Identifier insertion failed
} 

// Hash function to determine the index for a given identifier
int SymbolTable::hashf(string id) { 
	int asciiSum = 0; 

	for (int i = 0; i < id.length(); i++) { 
		asciiSum = asciiSum + id[i]; // Calculate the sum of ASCII values of characters in the identifier
	} 

	return (asciiSum % 100); // Return the hash value (modulus 100)
} 

// Driver code 
int main() { 
	SymbolTable st; // Create a symbol table object
	string check; 
	cout << "**** SYMBOL_TABLE ****\n"; 

	// Insert 'if' 
	if (st.insert("if", "local", "keyword", 4)) 
		cout << " -successfully"; 
	else
		cout << "\nFailed to insert.\n"; 

	// Insert 'number' 
	if (st.insert("number", "global", "variable", 2)) 
		cout << " -successfully\n\n"; 
	else
		cout << "\nFailed to insert\n"; 

	// Find 'if' 
	check = st.find("if"); 
	if (check != "-1") 
		cout << "Identifier Is present\n"; 
	else
		cout << "\nIdentifier Not Present\n"; 

	// Delete 'if' 
	if (st.deleteRecord("if")) 
		cout << "if Identifier is deleted\n"; 
	else
		cout << "\nFailed to delete\n"; 

	// Modify 'number' 
	if (st.modify("number", "global", "variable", 3)) 
		cout << "\nNumber Identifier updated\n"; 

	// Find and print 'number' 
	check = st.find("number"); 
	if (check != "-1") 
		cout << "Identifier Is present\n"; 
	else
		cout << "\nIdentifier Not Present"; 

	return 0; 
} 
