<?php
	/* Impliments a Queue class in PHP using a link list backend.
		Functions:
		__construct() - Constructor of the Queue class setting default values.
		BuildNewLink($key) - Accepts data and returns a new node to be put in the Queue.
		push($key) - Places data at the end of the Queue.
		pop() - Removes the first node in the Queue by pointing Root to the next node.
		size() - Returns the size of the Queue.
		front() - Returns the data at the front of the Queue unless size is 0.
	*/
	
	Class Queue{
	    private $Root;
	    private $next;
	    private $Qsize;
	    private $value;
	    	
	    public function __construct(){
	        $this -> Root = NULL;
	        $this -> next = NULL;
	        $this -> Qsize = 0;
	    }
	    
	    private function BuildNewNode($key){
			$node = new Queue;
			$node-> value = $key;
			return $node;
		}// end BuildNewNode(
	   
	    public function push($key){
	       // Build new node 
	       $node = $this->BuildNewNode($key);
	       
	       // Attach if Root is null
	       if ($this->Root == NULL)
	                $this->Root = $node;
	       // Else add onto link list
	       else{
	                $current = $this->Root;
	                $trail = NULL;
	                while ($current != NULL)
	                {
	                    $trail = $current;
	                    $current = $current -> next;
	                }
	                $trail->next = $node;
	         }
	         $this->Qsize++;
	    }//end push()
	    
	    public function pop(){
	        $this->Root = $this->Root->next;
	        $this->Qsize--;
	    }
	    
		public function size(){
	        return $this->Qsize;
	    }
	    
	    public function front(){
	        if ($this->Qsize > 0)
	        return $this->Root->value;
	        else
	            return NULL;
	    }
	}//end Class Queue
?>

