<?php
	// Queue Class used with Level Order printing nodes
	include 'Queue.php';
	
	/*
		Impliments an unbalanced Binary Search Tree in PHP
		Functions:
			__construct() - Sets default values and function pointers.
			InOrder() - Prints nodes in values from 0 - Z in the Tree.
			PreOrder() - Prints nodes as they were inserted into the Tree.
			PostOrder() - Prints nodes in reverse as they were inserted into the Tree.
			LevelOrder() - Prints nodes a level at a time in the Tree using a Queue.
			CopyTree() - Copies an old tree into a new one using PreOrderHelper().
	*/
	class Tree{
		// Private Memebers
		private $value;
		private $countof;
		private $NodeLevel;
		private $root;
		private $leftchild;
		private $rightchild;
		private $RaiseCountOfPointer;
		private $PrintNodePointer;
		private $CopyTreeHelperPointer;
		
		// Public Methods
		public function __construct(){
			$this->value = NULL;
			$this->countof = 0;
			$this->NodeLevel = 0;
			$this->root = NULL;
			$this->rightchild = NULL;
			$this->leftchild = NULL;
			$this->RaiseCountOfPointer = "RaiseCountOf";
			$this->PrintNodePointer = "PrintNode";
			$this->CopyTreeHelperPointer = "CopyTreeHelper";
		}
			
		public function Insert($key){
			$this->InsertHelper ($key,$this->RaiseCountOfPointer);
		}// end Insert()
		
		public function InOrder(){
			$this->InOrderHelper($this->root,$this->PrintNodePointer);	
		}
		
		public function PreOrder(){
			$this->PreOrderHelper($this->root,$this->PrintNodePointer);	
		}
		
		public function PostOrder(){
			$this->PostOrderHelper($this->root,$this->PrintNodePointer);	
		}
		
		public function LevelOrder(){
		    $this->LevelOrderHelper($this->root,$this->PrintNodePointer);
		}
		
		public function CopyTree($oldtree){
			$this->PreOrderHelper($oldtree->root,$this->CopyTreeHelperPointer);
		}
		
		// Private Methods
		private function CopyTreeHelper($node){
			if ($node->countof > 1)
				for ($i=0;$i<$node->countof;$i++)
					$this->Insert($node -> value);
			else
				$this->Insert($node -> value);
		}
			
		private function InsertHelper ($key,$UserFunction){
			
			// Track Level of the node
			$CurrentLevel = 0;
			
			if ($this->root == NULL)
			{
				$this->root = $this->BuildNewNode($key,0);
				return;
			}
			// else root is not null
			else{
				$current = $this->root;
				$trail = NULL;
				
				while($current != NULL)
				{
					$trail = $current;
					if ($key == $current->value)
					{
						$this->$UserFunction($current);
						return;	
					}
					if ($key < $current->value)
						$current = $current->leftchild;
					else
						$current = $current->rightchild;
					$CurrentLevel++;
				}//end while
				
				// Create leaf to insert
					$leaf = $this->BuildNewNode($key,$CurrentLevel);
				// Place leaf into the Tree
				if ($key < $trail->value)
					$trail->leftchild = $leaf;
				if ($key > $trail->value)
					$trail->rightchild = $leaf;	
			}//end else 	
		} // end InsertHelper
		
		private function BuildNewNode($key,$level){
			$node = new Tree;
			$node-> NodeLevel = $level;
			$node-> value = $key;
			$node-> countof = 1;
			return $node;
		}// end BuildNewNode()
		
		private function RaiseCountOf ($node){
			$node ->countof++;
		}
		
		private function PrintNode ($node){
			echo $node->value,'  [count of:',$node->countof,']','[level:',$node->NodeLevel,'] <br>';
		}
			
		private function InOrderHelper($node,$UserFunction){
			if ($node == NULL)
				return;
			else{
				$this->InOrderHelper($node->leftchild,$UserFunction);
				$this->$UserFunction($node);
				$this->InOrderHelper($node->rightchild,$UserFunction);
				return;				
			}//end else	
		}//end InOrderHelper()
	
		private function PreOrderHelper($node,$UserFunction){
			if ($node == NULL)
				return;
			else{
				$this->$UserFunction($node);
				$this->PreOrderHelper($node->leftchild,$UserFunction);
				$this->PreOrderHelper($node->rightchild,$UserFunction);
				return;				
			}//end else	
		}//end PreOrderHelper()
	
		private function PostOrderHelper($node,$UserFunction){
			if ($node == NULL)
				return;
			else{
				$this->PostOrderHelper($node->leftchild,$UserFunction);
				$this->PostOrderHelper($node->rightchild,$UserFunction);
				$this->$UserFunction($node);
				return;				
			}//end else	
		}//end PostOrderHelper()
		
		private function LevelOrderHelper($node,$UserFunction){
			$queue = new Queue;
			if ($this->root != NULL)
			    $queue->push($this->root);
			else{
			    echo 'Root is null';
			    return;
			}
			
			while ($queue->size() != 0)
			{
			    $node = $queue->front();
			    // Dequeue node
			    $queue->pop();
			    
			    // Add right child if it exist
			    if ($node->rightchild != NULL)
			        $queue->push($node->rightchild);
			        
			    // Add left child if it exist
			    if ($node->leftchild != NULL)
			        $queue->push($node->leftchild);
			        
			    // Print out level
			    $this->$UserFunction($node);
			}
		}//end LevelOrderHelper()
	} // end Tree class
		
?>