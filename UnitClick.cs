using UnityEngine;
using System.Collections;

//Unit Click Handling Script
//Written by Benjamin Malinowski
//
//This is the unit click handler script from a simple turn based strategy game that a small team and I developed together.
//This handles clicking on units on the game board, including determining if clicked unit was a friendly or enemy.
//It also handles the distance between the attacker and defender in the case of an attack, to be used in combat calculation.
//Script to script communication handles the acquisition of team information for each unit.
//

public class UnitClick : MonoBehaviour {

	public bool gridVisible;                  //Bool for if the movement grid is visible
	public gameManagerScript unitNameScript;  //gameManagerScript for unit name/details handling
	string lastActionTaken;                   //String for which type of action was last taken (move/attack)
	public GameObject clickedUnit;            //GameObject container for the unit clicked just now
	public GameObject unitAttacking;          //GameObject container for the unit that was previously clicked (for attack purposes)
	int activeTeam;                           //Int holding which team's turn it currently is
	int teamOfUnit;                           //Int holding which team the clicked unit is currently on

	// Use this for initialization
	void Start () {
		gridVisible = false;               //Set movement grid visible bool to initialize to false each run     
		Debug.Log ("UnitClick.cs Start");  //Debug console output for script start
	}
	
	// Update is called once per frame
	void Update () 
	{

	}
	
	void OnMouseDown()
	{
		GameObject ActionPlaceHolderGO = GameObject.Find ("clickedUnitTemp");
		lastActionTaken = ActionPlaceHolderGO.GetComponent<gameManagerScript> ().lastAction;                     //Pulls in the last action taken from gameManager script
		activeTeam = ActionPlaceHolderGO.GetComponent<gameManagerScript> ().activeTeam;                          //Pulls in the active team from gameManager script
		clickedUnit = this.gameObject;                                                                           //Sets clickedUnit game object to the clicked unit
		teamOfUnit = ActionPlaceHolderGO.GetComponent<gameManagerScript> ().returnTeamOfUnit(clickedUnit.name);  //Enters the unit(troops) stats script and returns the team of the clicked unit
		Debug.Log ("Unit Mouse Click Registered");                                                               //Debug console 'unit click registered' message

		if (gridVisible == false && lastActionTaken != "Attack" && teamOfUnit == activeTeam)                     //If the movement grid is invisible & the last action was not an attack & the clicked unit is on the active team...
		{
			unitNameScript.updateUnitName (clickedUnit);              //Update the unitNameScript with the name of the active unit
			foreach (Transform child in transform)                    //For each child object (menu buttons) of the parent game object (the clicked unit/troop)
            {                  
				if (child.gameObject.activeSelf == true)              //If the child object is active (menu buttons are visible)...
					child.gameObject.SetActive (false);               //Set them inactive
				else if (child.gameObject.activeSelf == false)        //If the child object is inactive (menu buttons are invisible)...
					child.gameObject.SetActive (true);                //Set them active
			}

		}
        else if (lastActionTaken == "Attack")  //If the last action taken was attack...
        {
			unitAttacking = ActionPlaceHolderGO.GetComponent<clickedUnitTempScript>().unitName;                       //Set unitAttacking to the unit that was last clicked (ie the attacker)
			unitNameScript.getVictimGO(clickedUnit);                                                                  //Retrieve the unit name of the defending unit from unitNameScript (the unit that was just clicked)
			float distance = Vector2.Distance (unitAttacking.transform.position, clickedUnit.transform.position);     //Find the distance between the two units.  This is for combat calculation later!
			Debug.Log("Distance : " + distance + "\n");                                                               //Sends distance to debug console
			unitNameScript.updateStats(distance);                                                                     //Sends distance between attacker and enemy into stat update function
        }
		Debug.Log ("Unit Mouse Click Script Complete");  //Debug console 'unit mouse click script complete' message
	}   //Combat initialize function is then called...
}
