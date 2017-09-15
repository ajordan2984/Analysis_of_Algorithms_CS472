<?php
	include 'Tree.php';

	// Fill first Tree with numbers
	$tree = new Tree;
	FillWithNumbers($tree);
	$tree -> LevelOrder();

	// Fill second Tree with words and numbers
	$secondtree = new Tree;
	parsefile($secondtree);
	$secondtree -> LevelOrder();
	
	
	// Function to fill tree with random numbers
	function FillWithNumbers($treeref){
		    for ($i = 0; $i<50;$i++)
			$treeref->Insert(rand(10,200));
	}// end FillWithNumbers()
	
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