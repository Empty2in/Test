#pragma once
#include <iostream>

template <class T>
class BinarySearchTree
{
private:

	template <class T>
	struct Node {
		T key_;
		Node<T>* left_;
		Node<T>* right_;
		Node<T>* p_;
		Node(T key, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* p = nullptr) : key_(key), left_(left), right_(right), p_(p) {}
	};

	Node<T>* root_;

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node<T>* iterativeSearchNode(const T& key) const;

	Node<T>* iterativeSearchMin(Node<T>* tree) const;
	Node<T>* iterativeSearchMax(Node<T>* tree) const;
	Node<T>* iterativeSearchParent(const Node<T>* tree) const;

	//// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
	//void printNode(std::ostream& out, Node<T>* root) const;
	//// 5.2 Рекурсивная функция определения количества узлов дерева
	//int getCount(const Node<T>* node) const;
	//// 6.2 Рекурсивная функция определения высоты дерева
	//int getHeight(const Node<T>* node) const;
	//// 8.2 Рекурсивная функция для инфиксного обхода узлов дерева.
	//void inorderWalk(Node<T>* node) const;

	void swap(BinarySearchTree<T>& scr);
	bool deleteNode(Node<T>* del);
	bool insertNode(Node<T>* newNode);
	

public:
	BinarySearchTree() : root_(nullptr) {};
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
	virtual ~BinarySearchTree();


	// 1.1 Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T& key) const;
	// 2 Вставка нового элемента в дерево: true, если элемент добавлен;
	// false, если элемент уже был
	bool insert(const T& key);
	// 3.1 Удаление элемента из дерева, не нарушающее порядка элементов
	// true, если элемент удален; false, если элемента не было
	bool deleteKey(const T& key);

	// 4.1 Печать строкового изображения дерева в выходной поток out,
	// использовать скобки, чтобы показать структуру дерева
	//void print(std::ostream& out) const;

	//// 5.1 Определение количества узлов дерева
	//int getCount() const;

	//// 6.1 Определение высоты дерева
	//int getHeight() const;

	//// 7 Инфиксный обход дерева (итеративный)
	//void iterativeInorderWalk() const;

	//// 8.1 Инфиксный обход дерева (рекурсивный)
	//void inorderWalk() const;

	//// 9 Обход двоичного дерева по уровням (в ширину).
	//void walkByLevels() const;

	//// 10 Являются ли два дерева похожими
	//bool isSimilar(const BinarySearchTree<T>& other) const;

	//// 11 Есть одинаковые ключи в двух деревьях поиска
	//bool isIdenticalKey(const BinarySearchTree<T>& other) const;

	bool isEmpty() const;
	bool deleteUnderTree(Node<T>* tree);

};


template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr) noexcept
{
	this->root_ = scr.root_;
	scr.root_ = nullptr;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept
{
	if (&src == this) {
		swap(src);
	}
	return *this;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteUnderTree(this->root_);
}

template<class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	return iterativeSearchNode(key);
}

template<class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node<T>* newNode = new Node<T>(key);
	if (insertNode(newNode)) {
		return true;
	}
	delete newNode;
	return false;
}

template<class T>
inline bool BinarySearchTree<T>::insertNode(Node<T>* newNode)
{
	if (newNode == nullptr) {
		return false;
	}
	if (isEmpty()) {
		this->root_ = newNode;
		return true;
	}
	Node<T>* temp = this->root_;
	while (temp != nullptr) {
		if (newNode->key_ < temp->key_) {
			if (temp->left_) {
				temp = temp->left_;
				continue;
			}
			else {
				temp->left_ = newNode;
				newNode->p_ = temp;
				return true;
			}
		}
		else if (newNode->key_ > temp->key_) {
			if (temp->right_) {
				temp = temp->right_;
				continue;
			}
			else {
				temp->right_ = newNode;
				newNode->p_ = temp;
				return true;
			}
		}
		else {
			return false;
		}
	};
}

template<class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	if (isEmpty()) {
		return false;
	}
	Node<T>* del = iterativeSearchNode(key);
	if (del == nullptr) {
		return false;
	}
	return deleteNode(del);
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	Node<T>* temp = this->root_;
	while (temp->key_ != key) {
		if (key < temp->key_) {
			temp = temp->left_;
			continue;
		}
		else {
			temp = temp->right_;
			continue;
		}
	}
	return temp;
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchMin(Node<T>* tree) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	if (tree == nullptr) {
		return tree;
	}
	Node<T>* temp = tree;
	while (temp->left_ != nullptr) {
		temp = temp->left_;
	}
	return temp;
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchMax(Node<T>* tree) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	Node<T>* temp = tree;
	while (temp->right_ != nullptr) {
		temp = temp->right_;
	}
	return temp;
}

template<class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchParent(const Node<T>* tree) const
{
	if (this->isEmpty()) {
		return nullptr;
	}
	if (tree == this->root_) {
		return nullptr;
	}
	Node<T>* temp = this->root_;
	Node<T>* parent = nullptr;
	while (temp && temp != tree) {
		parent = temp;
		if (temp->key_ > tree->key_) {
			temp = temp->left_;
		}
		else {
			temp = temp->right_;
		}
	}
	return parent;
}

template<class T>
void BinarySearchTree<T>::swap(BinarySearchTree<T>& scr)
{
	std::swap(this->root_, scr.root_);
}

template<class T>
inline bool BinarySearchTree<T>::deleteNode(Node<T>* del)
{
	Node<T>* par = iterativeSearchParent(del);
	if (del->right_ && del->left_) {
		Node<T>* newKey = iterativeSearchMin(del->right_);
		del->key_ = newKey->key_;
		deleteNode(newKey);
		return true;
	}
	else if (del->right_) {
		if (del == this->root_) {
			this->root_ = del->right_;
			del->right_->p_ = nullptr;
		}
		if (del == par->left_) {
			par->left_ = del->right_;
			del->right_->p_ = par;
		}
		else {
			par->right_ = del->right_;
			del->right_->p_ = par;
		}
	}
	else if (del->left_) {
		if (del == this->root_) {
			this->root_ = del->left_;
			del->left_->p_ = nullptr;
		}
		else if (del == del->p_->left_) {
			del->p_->left_ = del->left_;
		}
		else {
			del->p_->right_ = del->left_;
		}
	}
	else {
		if (del == this->root_) {
			delete del;
			return true;
		}
		else if (del == par->left_) {
			par->left_ = nullptr;
		}
		else {
			par->right_ = nullptr;
		}
	}
	delete del;
	return true;
}

template<class T>
inline bool BinarySearchTree<T>::isEmpty() const
{
	return this->root_ == nullptr;
}

template<class T>
bool BinarySearchTree<T>::deleteUnderTree(Node<T>* tree)
{
	if (tree) {
		deleteUnderTree(tree->left_);
		deleteUnderTree(tree->right_);
		delete tree;
		return true;
	};
	return false;
}
