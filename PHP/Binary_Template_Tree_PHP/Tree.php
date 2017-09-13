<?php
	class Tree{
		// Private Memebers
		private $value;
		private $countof;
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
			
			if ($this->root == NULL)
			{
				$this->root = $this->BuildNewNode($key);
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
				}//end while
				
				// Create leaf to insert
					$leaf = $this->BuildNewNode($key);
				// Place leaf into the Tree
				if ($key < $trail->value)
					$trail->leftchild = $leaf;
				if ($key > $trail->value)
					$trail->rightchild = $leaf;	
			}//end else 	
		} // end InsertHelper
		
		private function BuildNewNode($key){
			$node = new Tree;
			$node-> value = $key;
			$node-> countof = 1;
			return $node;
		}// end BuildNewNode()
		
		private function RaiseCountOf ($node){
			$node ->countof++;
		}
		
		private function PrintNode ($node){
			echo $node->value,"  [count of:",$node->countof,'] <br>';
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
		
	} // end Tree class
	
	
	// Test Code
	$tree = new Tree;
	parsefile($tree);
	$tree -> InOrder();
	$secondtree = new Tree;
	$secondtree -> CopyTree($tree);
	$secondtree -> InOrder();
	
	// Function to read in file
	function parsefile($treeref){
		$filename = "dat.txt";
		$filereader = fopen($filename,"r");
		$content = fread($filereader, filesize($filename));
		$lines = explode("\n",$content);
		
		foreach ($lines as $line)
		{
			$words = explode (" ",$line);
			foreach ($words as $word)
			{
				$NewWord = preg_replace('/[^a-z\d ]/i','',$word);
				if ($NewWord != NULL)
					$treeref->Insert(strtolower($NewWord));
			}
		}	
	}// end parsefile()
			
?>