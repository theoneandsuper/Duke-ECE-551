#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
	priority_queue_t pq;

	for (int i = 0; i < 257; i++) {
		if (counts[i] != 0) {
			Node * leaf = new Node(static_cast<unsigned>(i), counts[i]);
      			pq.push(leaf);
		}
	}

	if (pq.empty()) {
		return NULL;
	}

	while (pq.size() > 1) {
		Node * left = pq.top();
		pq.pop();
		Node * right = pq.top();
		pq.pop();

		Node * parent = new Node(left, right);
		pq.push(parent);
	}

	//last one to be the root
	return pq.top();
}  
