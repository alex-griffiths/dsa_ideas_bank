#define LH +1 // Left High
#define EH 0  // Even High
#define RH -1 // Right High

template <class Type>
struct Node {
	Type data;
	Node *left;
	Node *right;
	int  bal;
};


template <class Type, class KType>
class AVLTree {
	protected:
	int count;
	Node<Type> *tree;
	Node<Type> *_insert(Node<Type> *root, Node<Type> *new_ptr, bool &taller);
	Node<Type> *left_balance(Node<Type> *root, bool &taller);
	Node<Type> *rotate_left(Node<Type> *root);
	Node<Type> *right_balance(Node<Type> *root, bool &taller);
	Node<Type> *rotate_right(Node<Type> *root);
	Node<Type> *_delete(Node<Type> *root, KType delete_key, bool &shorter, bool &success);
	Node<Type> *delete_left_balance(Node<Type> *root, bool &shorter);
	Node<Type> *delete_right_balance(Node<Type> *root, bool &shorter);
	Node<Type> *_retrieve(KType key, Node<Type> *root);
	
	void _traversal(void(*process)(Type data_proc), Node<Type> *root);
	void _destroy_avl(Node<Type> *root);
	void _print(Node<Type> *root, int level);
	
	public:
	AVLTree(void);
	~AVLTree(void);
	bool AVL_insert(Type data_in);
	bool AVL_delete(KType delete_key);
	bool AVL_retrieve (KType key, Type &data_out);
	void AVL_traverse(void (*process)(Type data_proc));
	
	bool AVL_empty(void);
	bool AVL_full(void);
	int  AVL_count(void);
	
	void AVL_print(void);
};

template <class Type, class KType>
AVLTree<Type, KType>::AVLTree(void) {
	tree  = NULL;
	count = 0;
}

template <class Type, class KType>
bool AVLTree<Type, KType>::AVL_insert(Type data_in) {
	Node<Type> *new_ptr;
	bool taller;
	if (!(new_ptr == new Node<Type>)) {
		cout << data_in.key << endl;
		return false;
	}
	
	new_ptr->bal   = EH;
	new_ptr->right = NULL;
	new_ptr->left  = NULL;
	new_ptr->data  = data_in;
	
	tree = _insert(tree, new_ptr, taller);
	count++;
	
	return true;
}


template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::_insert(Node<Type> *root, Node<Type> *new_ptr, bool &taller) {
	
	// Check if null tree.
	if (!root) {
		root = new_ptr;
		taller = true;
		
		return root;
	}
	
	if (new_ptr->data.key < root->data.key) {
		root->left = _insert(root->left, new_ptr, taller);
		
		if (taller) {
			switch(root->bal) {
				
				// Was left high -- rotate.
				case LH: {
					root = left_balance(root, taller);
				} break;
				
				// Was balanced. Now left high.
				case EH: {
					root->bal = LH;
				} break;
				
				case RH: {
					root->bal = EH;
					taller = false;
				} break;
			}
		} 
	} else {
		root->right = _insert(root->right, new_ptr, taller);
		
		if (taller) {
			switch(root->bal) {
				// Was left high -- rotate.
				case LH: {
					root->bal = EH;
					taller = false;
				} break;
				
				// Was balanced. Now left high.
				case EH: {
					root->bal = RH;
				} break;
				
				case RH: {
					root = right_balance(root, taller);
				} break;
			}
		}
	}
	
	return root;
}

template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::left_balance(Node<Type> *root, bool &taller) {
	Node<Type> *right_tree;
	Node<Type> *left_tree;
	
	left_tree = root->left;
	switch(left_tree->bal) {
		case LH: {
			root->bal = EH;
			left_tree->bal = EH;
			
			root = rotate_right(root);
			taller = false;
		} break;
		
		case EH: {
			// Error, we shouldn't be trying to balance an equal height node.
			cout << "\n\a\aError in left_balance\n";
			exit(100);
		}
		
		case RH: {
			right_tree = left_tree->right;
			
			switch(right_tree->bal) {
				case LH: {
					root->bal      = RH;
					left_tree->bal = EH;
				} break;
				
				case EH: {
					root->bal      = EH;
					left_tree->bal = EH;
				} break;
				
				case RH: {
					root->bal      = EH;
					left_tree->bal = EH;
				} break;
			}
			
			right_tree->bal = EH;
			
			root->left = rotate_left(left_tree);
			
			root = rotate_right(root);
			taller = false;
		} break;
	}
	
	return root;
}


template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::rotate_left(Node<Type> *root) {
	Node<Type> *temp_ptr;
	
	temp_ptr = root->right;
	root->right = temp_ptr->left;
	temp_ptr->left = root;
	
	return temp_ptr;
}

template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::rotate_right(Node<Type> *root) {
	Node<Type> *temp_ptr;
	
	temp_ptr = root->left;
	root->left = temp_ptr->right;
	temp_ptr->right = root;
	
	return temp_ptr;
}

template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::right_balance(Node<Type> *root, bool &taller) {
	Node<Type> *right_tree;
	Node<Type> *left_tree;
	
	right_tree = root->right;
	
	switch(right_tree->bal) { 
		case LH: {
			left_tree = right_tree->left;
			
			switch(left_tree->bal) {
				case RH: {
					root->bal = LH;
					right_tree->bal = EH;
				} break;
				
				case EH: {
					root->bal = EH;
					right_tree->bal = EH;
				} break;
				
				case LH: {
					root->bal = EH;
					right_tree->bal = RH;
				} break;
			}
		} break;
		
		case EH: {
			root->bal = EH;
			taller = false;
		} break;
		
		case RH: {
			root->bal = EH;
			right_tree->bal = EH;
			
			root = rotate_right(root);
			taller = false;
		} break;
	}
	return root;
}

template <class Type, class KType>
bool AVLTree<Type, KType>::AVL_delete(KType delete_key) {
	bool shorter;
	bool success;
	
	Node<Type> *new_root;
	
	new_root = _delete(tree, delete_key, shorter, success);
	if (success) {
		tree = new_root;
		count--;
	}
	
	return success;
}


template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::_delete(Node<Type> *root, KType delete_key, bool &shorter, bool &success) {
	Node<Type> *delete_ptr, *exchange_ptr, *new_root;
	
	if (!root) {
		shorter = false;
		success = false;
		
		return NULL;
	}
	
	if (delete_key < root->data.key) {
		root->left = _delete(root->left, delete_key, shorter, success);
		
		if (shorter) {
			root = delete_right_balance(root, shorter);
		}
	} else if (delete_key > root->data.key) {
		root->right = _delete(root, delete_key, shorter, success);
		
		if (shorter) {
			root = delete_left_balance(root, shorter);
		}
	} else {
		delete_ptr = root;
		
		if (!root->right) {
			new_root = root->left;
			success = true;
			shorter = true;
			
			delete(delete_ptr);
			return new_root;
		} else if (!root->left) {
			new_root = root->right;
			success = true;
			shorter = true;
			delete(delete_ptr);
			return new_root;
		} else {
			exchange_ptr = root->left;
			while (exchange_ptr->right) {
				exchange_ptr = exchange_ptr->right;
			}
			
			root->data = exchange_ptr->data;
			root->left = _delete(root->left, exchange_ptr->data.key, shorter, success);
			
			if (shorter) {
				root = delete_right_balance(root, shorter);
			}
		}
	}
	
	return root;
}

template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::delete_left_balance(Node<Type> *root, bool &smaller) {
	Node<Type> *right_tree;
	Node<Type> *left_tree;
	
	switch (root->bal) { 
		case RH: {
			root->bal = EH;
		} break;
		
		case EH: {
			root->bal = LH;
			smaller = false;
		} break;
		
		case LH: {
			left_tree = root->left;
			
			switch (left_tree->bal) {
				case LH:
				case EH: {
					if (left_tree->bal == EH) {
						root->bal = LH;
						left_tree->bal = RH;
						smaller = false;
					} else {
						root->bal = EH;
						left_tree->bal = EH;
					}
					
					root = rotate_right(root);
				} break;
				
				case RH: {
					right_tree = left_tree->right;
					switch (right_tree->bal) {
						case LH: {
							root->bal = RH;
							left_tree->bal = EH;
						} break;
						
						case EH: {
							root->bal = EH;
							left_tree->bal = EH;
						} break;
						
						case RH: {
							root->bal = EH;
							left_tree->bal = LH;
						} break;
					}
					
					right_tree->bal = EH;
					root->left = rotate_left(left_tree);
					root = rotate_right(root);
				} break;
			}
		}
	}
	
	return root;
}

template <class Type, class KType>
Node<Type> *AVLTree<Type, KType>::delete_right_balance(Node<Type> *root, bool &shorter) {
	Node<Type> *right_tree, *left_tree;
	
	switch (root->bal) {
		case LH: {
			root->bal = EH;
		} break;
		
		case EH: {
			root->bal = RH;
			shorter = false;
		} break;
		
		case RH: {
			right_tree = root->right;
			if (right_tree->bal == LH) {
				left_tree = right_tree->left;
				
				switch(left_tree->bal) {
					case LH: {
						right_tree->bal = RH;
						root->bal = EH;
					} break;
					
					case EH: {
						root->bal = EH;
						right_tree->bal = EH;
					} break;
					
					case RH: {
						root->bal = LH;
						right_tree->bal = EH;
					} break;
				}
				
				left_tree->bal = EH;
				
				root->right = rotate_right(right_tree);
				root = rotate_right(root);
			} else {
				switch (rightTree->bal) {
					case LH:
					case RH: {
						root->bal      = EH;
						rightTree->bal = EH;
					} break;
					
					case EH: {
						root->bal      = RH;
						rightTree->bal = LH;
						shorter        = false;
					} break;
				}
				root = rotateLeft (root);
			} 
		} break;
	}
	
	return root;
}

template <class Type, class KType>
bool AVLTree<Type, KType>::AVL_retrieve(KType key, Type &data_out) {
	Node<Type> *node;
	
	if (!tree) {
		return false;
	}
	
	node = _retrieve(key, tree);
	
	if (node) {
		data_out = node->data;
		return true;
	} else { 
		return false;
	}
}

template <class Type, class KType>
Node<Type>* AVLTree<Type, KType>::_retrieve(KType key, Node<Type> *root) {
	if (root) {
		if (key < root->data.key) {
			return _retrieve(key, root->left);
		} else if (key > root->data.key) {
			return _retrieve (key, root->right);
		} else {
			return root;
		}
	} else {
		return root;
	}
}

template <class Type, class KType>
void AVLTree<Type, KType>::AVL_traverse(void(*process)(Type data_proc)) {
	_traversal(process, tree);
	return;
}

template <class Type, class KType>
void AVLTree<Type, KType>::_traversal(void(*process)(Type data_proc), Node<Type> *root) {
	if (root) {
		_traversal(process, root->left);
		process(root->data);
		_traversal(process, root->right);
	}
	
	return;
}

template <class Type, class KType>
bool AVLTree<Type, KType>::AVL_empty() {
	return (count == 0);
}

template <class Type, class KType>
bool AVLTree<Type, KType>::AVL_full() {
	Node<Type> *new_ptr;
	
	new_ptr = new Node<Type>;
	
	if (new_ptr) {
		delete new_ptr;
		return false;
	} else {
		return true;
	}
}

template <class Type, class KType>
int AVLTree<Type, KType>::AVL_count() {
	return count;
}

template <class Type, class KType>
AVLTree<Type, KType>::~AVLTree() {
	if (tree) {
		_destroy_avl(tree);
	}
}

template <class Type, class KType>
void AVLTree<Type, KType>::_destroy_avl(Node<Type> *root) {
	if (root) {
		_destroy_avl(root->left);
		_destroy_avl(root->right);
		delete root;
	}
	
	return;
}

template <class Type, class KType>
void AVLTree<Type, KType>::AVL_print() {
	_print(tree, 0);
	return;
}

template <class Type, class KType>
void AVLTree<Type, KType>::_print(Node<Type> *root, int level) {
	int i;
	
	if (root) {
		_print(root->right, level + 1);
		
		cout << "bal " << setw(3) << root->bal << ": Level " << setw(3) << level;
		
		for (i = 0; i <= level; i++) {
			cout << "....";
			cout << setw(3) << root->data.key;
			
			vector<int> ids = root->data.id_list;
			
			for(vector<int>::iterator it = ids.begin(); it != ids.end(); it++) {
				cout << it << ", ";
			}
			
			if (root->bal == LH) {
				cout << " (LH)" << endl;
			} else if (root->bal == RH) {
				cout << " (RH)" << endl;
			} else {
				cout << " (EH)" << endl;
			}
		}
		
		_print(root->right, level + 1);
	}
}