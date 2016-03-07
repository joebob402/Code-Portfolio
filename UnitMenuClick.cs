using UnityEngine;
using System.Collections;

//Unit Tactics Menu Handling Script
//Written by Benjamin Malinowski
//
//This is the unit tactics menu click handler script from a simple turn based strategy game that a small team and I developed together.
//This ensures that when a unit's tactics menu is displayed, that the correct action is registered depending on which button was clicked.
//This includes displaying the blue movement grid tiles for MOVE, instancing red attack tiles from prefab for ATTACK, and hiding the menu for CANCEL.
//

public class UnitMenuClick : MonoBehaviour {

	public clickedUnitTempScript lastActionHolder;

	int selectedUnitMovementRange;
	int selectedUnitAttackRange;

	GameObject attackTilePrefab;
	GameObject attackTileClone;

	// Use this for initialization
	void Start () { 

    }
	
	// Update is called once per frame
	void Update () {
	
	}
	void OnMouseDown()
	{
		GameObject thisUnit = this.gameObject;                                           //On click of unit menu option, set unit menu button as thisUnit (unit menu buttons are children of parents aka units/troops)
		thisUnit = thisUnit.transform.parent.gameObject;                                 //Set thisUnit to be the parent of clicked menu button (ie the unit/troop)                          

		if (thisUnit.name == "Barbarian" || thisUnit.name == "Evil Barbarian") {         //Check the name of the active unit...
			selectedUnitMovementRange = 5;                                               //Set movement and attack               
			selectedUnitAttackRange = 3;                                                 //range accordingly...
		}
		else if (thisUnit.name == "Paladin"  || thisUnit.name == "Evil Paladin") {       //Repeat...
			selectedUnitMovementRange = 4;
			selectedUnitAttackRange = 2;
		}
		else if (thisUnit.name == "Silver Dwarf" || thisUnit.name == "Evil Silver Dwarf") {
			selectedUnitMovementRange = 4;
			selectedUnitAttackRange = 2;
		}
		else if (thisUnit.name == "Elf Mage"  || thisUnit.name == "Evil Elf Mage") {
			selectedUnitMovementRange = 5;
			selectedUnitAttackRange = 3;
		}
		else if (thisUnit.name == "Silver Knight"  || thisUnit.name == "Evil Silver Knight") {
			selectedUnitMovementRange = 4;
			selectedUnitAttackRange = 2;
		}
		else if (thisUnit.name == "Hammer Dwarf"  || thisUnit.name == "Evil Hammer Dwarf") {
			selectedUnitMovementRange = 4;
			selectedUnitAttackRange = 2;
		}
		else if (thisUnit.name == "Wizard"  || thisUnit.name == "Evil Wizard") {
			selectedUnitMovementRange = 3;
			selectedUnitAttackRange = 4;
		}
		else if (thisUnit.name == "Berserker"  || thisUnit.name == "Evil Berserker") {
			selectedUnitMovementRange = 5;
			selectedUnitAttackRange = 2;
		}
		else if (thisUnit.name == "Kite Shield Knight"  || thisUnit.name == "Evil Kite Knight") {
			selectedUnitMovementRange = 3;
			selectedUnitAttackRange = 2;
		}
		else if (thisUnit.name == "Fencer Knight"  || thisUnit.name == "Evil Fencer Knight") {
			selectedUnitMovementRange = 4;
			selectedUnitAttackRange = 2;
		}
        Debug.Log("Unit Menu Mouse Click Registered");  //Debug console successful stat set check                                     

		GameObject clickedOption = this.gameObject;                                                                                                                  //Set clickedOption as the unit menu button that was clicked   
                                                                                                                       
		if (clickedOption.name == "movebutton" && clickedOption.renderer.enabled == true)                                                                            //If move unit menu button was clicked, find movement tiles in movement range and render
		{
            lastActionHolder.ActionTaken("Move");                                                                                                                    //Sets the last action taken container to 'move'
            foreach (GameObject gameObj2 in GameObject.FindObjectsOfType<GameObject>())                                                                              //Searches through game objects to find all movement grid tiles
			{
				if(gameObj2.name == "tileGrass(Clone)" && Vector3.Distance (thisUnit.transform.position, gameObj2.transform.position) <= selectedUnitMovementRange)  //If game object is a movement grid tile & within the movement range of the selected unit
			    {
				    gameObj2.renderer.enabled = true;                                                                                                                //Renders them active
			    }
			    if(gameObj2.name == "movebutton" || gameObj2.name == "attackButton" || gameObj2.name == "cancelButton")                                              //If found object is unit menu button
			    {
				    gameObj2.SetActive(false);                                                                                                                       //Renders them inactive
			    }
		    }
	   }

	   if (clickedOption.name == "attackbutton" && clickedOption.renderer.enabled == true )                                                                          //If attack button was clicked, attack grid is instantiated
	   {
            lastActionHolder.ActionTaken("Attack");                                                                                                                  //Sets the last action taken container to 'attack'
            foreach (GameObject gameObj2 in GameObject.FindObjectsOfType<GameObject>())                                                                              //Searches through game objects to find all movement grid tiles
			{				
                if(gameObj2.name == "tileGrass(Clone)" && Vector3.Distance (thisUnit.transform.position, gameObj2.transform.position) <= selectedUnitAttackRange)    //If game object is movement grid tile & within the attack range of the selected unit
				{
			        attackTileClone = Instantiate (attackTilePrefab) as GameObject;                                                                                  //Create a new instance of the red attack grid tile from the prefab (destroyed after combat)
					attackTileClone.transform.position = gameObj2.transform.position;                                                                                //Transform the tile to the position of the movement grid
				}
			    if(gameObj2.name == "movebutton" || gameObj2.name == "attackbutton" || gameObj2.name == "cancelbutton")                                              //If found object is unit menu button
			    {
				    gameObj2.SetActive(false);                                                                                                                       //Renders them inactive
				}
			}
		}

		if (clickedOption.name == "cancelbutton" && clickedOption.renderer.enabled == true)                              //If cancel button was clicked, hide unit menu
		{
			foreach (GameObject gameObj2 in GameObject.FindObjectsOfType<GameObject>())                                  //Searches through game objects to find all grass tiles
			{
				if(gameObj2.name == "movebutton" || gameObj2.name == "attackbutton" || gameObj2.name == "cancelbutton")  //If found object is unit menu button...
                {
					gameObj2.SetActive(false);                                                                           //Renders them inactive
				}
			}
		}
		Debug.Log ("Unit Menu Mouse Click Script Complete");  //Debug console successful run check
	}
}
