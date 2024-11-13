struct node_t{
    char* data;
    node_t* left;
    node_t* right;
};

node_t* CreateNode(char* value);
void Print (node_t* node);
void DestructNode(node_t* node);
void export_tree_to_dot(node_t* root, const char* filename);
void Akinator(node_t* node);
void ReadTreeFromFile(node_t** node, const char* file_with_tree);