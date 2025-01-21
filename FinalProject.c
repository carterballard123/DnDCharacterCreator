#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct Character {
    char name[25];            // Character's name (up to 24 characters + null terminator)
    int level;                // Character's current level (determines power and abilities)
    struct Class *class;      // Pointer to the character's class (e.g., Fighter, Wizard)
    char background[12];      // Character's background (e.g., Noble, Soldier, Outlander)
    char race[12];            // Character's race (e.g., Human, Elf, Dwarf)
    char alignment[16];       // Character's alignment (e.g., Lawful Good, Chaotic Evil)
    int strength;             // Character's Strength score (affects physical power)
    int dexterity;            // Character's Dexterity score (affects agility and reflexes)
    int constitution;         // Character's Constitution score (affects health and stamina)
    int intelligence;         // Character's Intelligence score (affects knowledge and reasoning)
    int wisdom;               // Character's Wisdom score (affects perception and insight)
    int charisma;             // Character's Charisma score (affects influence and charm)
    int speed;                // Character's movement speed (measured in feet per round)
    int armorClass;           // Character's Armor Class (determines how hard they are to hit)
    struct Armor *armor;      // Pointer to the character's equipped armor
    struct Weapon *weapon;    // Pointer to the character's equipped weapon
    int hasShield;            // Boolean indicating if the character has a shield (1 = yes, 0 = no)
    int proficiencyModifier;  // Character's proficiency modifier (based on level)
    int HP;                   // Character's current hit points (health value)
    struct Character *next;   // Pointer to the next character in a linked list
};

struct Armor {
    char *name;            // Name of the armor (e.g., "Chain Mail", "Leather Armor")
    char *type;            // Category of armor (e.g., "Light", "Medium", "Heavy")
    int baseAC;               // Base Armor Class provided by this armor
    int maxDexBonus;          // Maximum Dexterity modifier allowed with this armor (e.g., 2 for medium armor)
    int requiresDexCap;       // Boolean indicating if the Dexterity modifier is capped (1 = capped, 0 = uncapped)
    int stealthDisadvantage;  // Boolean indicating if this armor imposes disadvantage on Stealth checks (1 = yes, 0 = no)
};

struct Armor armors[13];        // Array to hold all of the data that armors.txt has

struct Weapon {
    char *name;            // Name of the weapon (e.g., "Longsword", "Shortbow")
    char *type;            // Category of weapon (e.g., "Melee", "Ranged")
    char *damageType;      // Type of damage dealt (e.g., "Slashing", "Piercing", "Bludgeoning")
    char *damageDice;       // Damage dice for the weapon (e.g., "1d8", "2d6")
    char *twoHandDamage;    // Damage dice when used with two hands (if the weapon is versatile)
    int isFinesse;            // Boolean indicating if the weapon can use Dexterity for attack/damage rolls (1 = yes, 0 = no)
    int isVersatile;          // Boolean indicating if the weapon can be used one- or two-handed (1 = yes, 0 = no)
    int isTwoHanded;          // Boolean indicating if the weapon requires two hands to wield (1 = yes, 0 = no)
    int range[2];             // Weapon's range: [minimum range, maximum range] (e.g., {0, 60} for a thrown weapon)
    int isLight;              // Boolean indicating if the weapon is light (suitable for dual-wielding) (1 = yes, 0 = no)
    int isHeavy;              // Boolean indicating if the weapon is heavy (unsuitable for small creatures) (1 = yes, 0 = no)
    int isReach;              // Boolean indicating if the weapon has extended reach (1 = yes, 0 = no)
};

struct Weapon weapons[31];      // Array to hold all of the data that weapons.txt has

struct Class {
    char *name;         // Name of the class (e.g., "Fighter", "Wizard", "Rogue")
    char *subClass;     // Name of the subclass or specialization (e.g., "Champion", "Evoker")
    char *hitDie;          // Hit die used for determining hit points (e.g., "1d8", "1d10")
};

char *attributes[6];    // Array to hold all of the data that armors.txt has

char *alignments[9];    // Array to hold all of the data that armors.txt has

char *races[10];         // Array to hold all of the data that armors.txt has

char *backgrounds[16];   // Array to hold all of the data that armors.txt has

char *classes[12][5];  // Array to hold all of the data that armors.txt has

// Utility functions
void inputBuffer(void);
int isValidInput(int *userInput, int floor, int ceiling);
int isValidName(char *name);

// File Loading functions
void loadArmors(const char *filename);
void freeArmors(void);
void loadWeapons(const char *filename);
void freeWeapons(void);
void loadFilesTo2DArray(const char *filename, char **array, int i);
void free2DArray(char **array, int size);
void loadClassesFromFile(const char *filename);
void freeClasses(void);
void loadCharactersFromFile(struct Character **currCharacter);
void initializeGlobalArrays(void);

// Armor functions
const char *armorRequirement(struct Armor *armor);
const char *armorStealth(struct Armor *armor);

// Weapon functions
const char *weaponFinesse(struct Weapon *weapon);
const char *weaponVersatile(struct Weapon *weapon);
const char *weaponRange(struct Weapon *weapon);

// Selecting functions (adding updating character data)
void selectName(struct Character *character);
int selectLevel(struct Character *character);
void selectClass(struct Character *character);
void selectSubClass(struct Character *character);
void selectBackground(struct Character *character);
void selectRace(struct Character *character);
void selectAlignment(struct Character *character);
void selectAttributes(struct Character *character);
void selectArmor(struct Character *newCharacter);
void selectWeapon(struct Character *character);
void selectShield(struct Character *character);

// Calculate functions
// calculateModifier: Converts an attribute value into its corresponding modifier.
int calculateModifier(int attribute); 
// calculateArmorClass: Calculates Armor Class based on Dexterity, armor type, and shield status.
int calculateArmorClass(int dexterity, const char *armorName, int hasShield); 
// calculateRollModifier: Computes a D20 roll with a modifier based on character attributes.
int calculateRollModifier(struct Character *head, char *diceCharacterName, int numChoice); 
// calculateDamageDiceRoll: Calculates the damage roll based on weapon type.
int calculateDamageDiceRoll(struct Weapon *weapon);
// calculateDamageRoll: Calculates total damage, including modifiers and weapon effects.
int calculateDamageRoll(struct Character *character, char *characterName);
// calculateAttackRoll: Computes the attack roll, factoring in modifiers and weapon.
int calculateAttackRoll(struct Character *character, char *characterName);
// calculateHealth: Calculates health points based on level and Constitution modifier.
int calculateHealth(struct Character *character);
// calculateProficiencyModifier: Determines the proficiency modifier based on character level.
int calculateProficiencyModifier(struct Character *character); 

// Display functions:
// Adds a new character to the character list. The head pointer is modified to point to the new character.
void addCharacter(struct Character **head);
// Displays all the characters in the list, printing their details in a readable format.
void displayCharacter(struct Character *head); 
// Searches for a character by name in the character list and prints the character's details if found.
void searchCharacter(struct Character *head, char *searchName); 
// Updates the data of an existing character in the list. The character is identified by its name, and the new data is applied.
void updateCharacter(struct Character *head, char *updateCharacterName); 
// Deletes a character from the list based on its name. The character is removed, and the list is restructured.
void deleteCharacter(struct Character **head, char *deleteCharacterName);
// Levels up a character by increasing its level and applying relevant changes to the character's stats.
void levelUpCharacter(struct Character *character, char *levelCharacterName);
// Prompts the user to type in their characters name to find the character
void getCharacterName(char *name, const char *prompt);

// Dice rolling function
int rollD20(void);  // Rolls a D20
int rollD12(void);  // Rolls a D12
int rollD10(void);  // Rolls a D10
int rollD8(void);   // Rolls a D8
int rollD6(void);   // Rolls a D6
int rollD4(void);   // Rolls a D4

int main(){

    initializeGlobalArrays();

    srand(time(NULL));          // Seeds a random number

    char userCharacter[25];     // Users character name input
    int userChoice;             // Users choice input
    struct Character *characterList = NULL;
    loadCharactersFromFile(&characterList);

    printf("\nWelcome to the DnD Character Creator!\n");

    do{
        // Display menu options
        printf("\n1. Add a new character\n");
        printf("2. Level up your character\n");
        printf("3. Display character\n");
        printf("4. Search for character\n");
        printf("5. Update character\n");
        printf("6. Delete character\n");
        printf("7. Dice rolling menu\n");
        printf("8. Exit DnD Character Creator\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice); //user's choice

        // Based on user input:
        switch (userChoice) {
            case 1:
                addCharacter(&characterList);
                break;
            case 2:
                getCharacterName(userCharacter, "Enter the name of the character to level up: ");
                levelUpCharacter(characterList, userCharacter);
                break;
            case 3:
                displayCharacter(characterList);
                break;
            case 4:
                getCharacterName(userCharacter, "Enter the name of the character to search for: ");
                searchCharacter(characterList, userCharacter);
                break;
            case 5:
                getCharacterName(userCharacter, "Enter the name of your character to update: ");
                updateCharacter(characterList, userCharacter);
                break;
            case 6: 
                getCharacterName(userCharacter, "Enter the name of your character to delete: ");
                deleteCharacter(&characterList, userCharacter); 
                break;
            case 7:
                do {
                    printf("\n1. Roll a D20\n");
                    printf("2. Roll a D20 with modifiers\n");
                    printf("3. Make an attack role with currently equipped weapon\n");
                    printf("4. Roll for damage with currently equipped weapon\n");
                    printf("5. Exit dice rolling menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &userChoice);

                    switch (userChoice) {
                        case 1:
                            printf("You rolled: %d\n\n", rollD20());
                            break;
                        case 2:
                            getCharacterName(userCharacter, "Enter the name of your character: ");
                            printf("Enter which modifier to add on to your roll:\n");
                            printf("1. Strength\n");
                            printf("2. Dexterity\n");
                            printf("3. Constitution\n");
                            printf("4. Intelligence\n");
                            printf("5. Wisdom\n");
                            printf("6. Charisma\n");
                            printf("7. None\n");
                            printf("Enter your choice: ");
                            scanf("%d", &userChoice);
                            printf("You rolled: %d\n\n", calculateRollModifier(characterList, userCharacter, userChoice));
                            break;
                        case 3:
                            getCharacterName(userCharacter, "Enter the name of your character you would like to attack with: ");
                            printf("You rolled: %d\n\n", calculateAttackRoll(characterList, userCharacter));
                            break;
                        case 4:
                            getCharacterName(userCharacter, "Enter the name of your character you would like roll for damage with: ");
                            printf("You rolled: %d\n\n", calculateDamageRoll(characterList, userCharacter));
                            break;
                        case 5:
                            break;
                        default:
                            printf("\nInvalid choice, please try again...\n\n");
                            break;
                    }
                } while(userChoice != 5);
                break;
            case 8:
                printf("Exiting DnD Character Creator...\n");
                break;
            default:
                printf("\nInvalid choice, please try again...\n\n");
                break;
        }
    } while(userChoice != 8);

    struct Character *temp;
        while (characterList != NULL) {
            temp = characterList;
            characterList = characterList->next;
            free(temp);
        }

    freeArmors();
    freeWeapons();
    free2DArray(attributes, 6);
    free2DArray(alignments, 9);
    free2DArray(races, 10);
    free2DArray(backgrounds, 16);
    void freeClasses();
    return 0;
}

// Utility functions
void inputBuffer(void){
    while (getchar() != '\n');
}

int isValidInput(int *userInput, int floor, int ceiling) {

     // Check if input is a valid integer
    if (scanf("%d", userInput) != 1) {
        printf("Invalid input. Please enter a number.\n\n");
        inputBuffer();  // Clear the buffer if input is invalid
        return 0;  // Invalid input
    }

    if (*userInput < floor || *userInput > ceiling) {
        printf("Invalid choice, please enter a number between %d and %d.\n\n", floor, ceiling);
        return 0;  // Invalid input
    }
    return 1;  // Valid input
}

int isValidName(char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (isdigit(name[i])) {
            printf("Invalid name, names cannot contain digits...\n\n");
            return 0;  // Invalid name, contains a digit
        }
    }
    return 1;  // Valid name, no digits
}

// File Loading Functions
void loadArmors(const char *filename) {

    char buffer[256];
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL && count < 13) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Temporary buffers for parsing
        char tempName[256], tempType[256];
        int baseAC, dexBonus, stealthDisadvantage, requiresDexCap;

        // Parse the line
        if (sscanf(buffer, "%255[^,],%255[^,],%d,%d,%d,%d", tempName, tempType, &baseAC, &dexBonus, &stealthDisadvantage, &requiresDexCap) != 6) {
            fprintf(stderr, "Error parsing line: %s\n", buffer);
            fclose(file);
            return;
        }

        // Allocate memory for the name and type fields
        armors[count].name = malloc(strlen(tempName) + 1);
        armors[count].type = malloc(strlen(tempType) + 1);

        if (armors[count].name == NULL || armors[count].type == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            return;
        }

        // Copy the parsed strings into the dynamically allocated memory
        strcpy(armors[count].name, tempName);
        strcpy(armors[count].type, tempType);

        // Populate the remaining fields
        armors[count].baseAC = baseAC;
        armors[count].maxDexBonus = dexBonus;
        armors[count].requiresDexCap = requiresDexCap;
        armors[count].stealthDisadvantage = stealthDisadvantage;

        count++;
    }

    fclose(file);

    if (count != 13) {
        fprintf(stderr, "Error: Expected %d armors, but loaded %d.\n", 13, count);
    }
}

void freeArmors(void) {
    for (int i = 0; i < 13; i++) {
        free(armors[i].name);
        free(armors[i].type);
    }
}

void loadWeapons(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[512];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL && count < 31) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        // Temporary buffers for parsing
        char tempName[256], tempType[256], tempDamageType[256], tempDamageDice[256], tempTwoHandedDamage[256];
        int tempIsFinesse, tempIsVersatile, tempIsTwoHanded, tempIsLight, tempIsHeavy, tempIsReach, range1, range2;

        // Parse the line using sscanf
        int result = sscanf(buffer, "%255[^,],%255[^,],%255[^,],%255[^,],%255[^,],%d,%d,%d,%d,%d,%d,%d,%d", tempName, tempType, tempDamageType, tempDamageDice, tempTwoHandedDamage, &tempIsFinesse, &tempIsVersatile, &tempIsTwoHanded, &range1, &range2, &tempIsLight, &tempIsHeavy, &tempIsReach);

        if (result != 13) {
            fprintf(stderr, "Error parsing line: %s\n", buffer);
            continue;
        }

        // Allocate memory for name, type, damageType, damage, and range
        weapons[count].name = malloc(strlen(tempName) + 1);
        weapons[count].type = malloc(strlen(tempType) + 1);
        weapons[count].damageType = malloc(strlen(tempDamageType) + 1);
        weapons[count].damageDice = malloc(strlen(tempDamageDice) + 1);
        weapons[count].twoHandDamage = malloc(strlen(tempTwoHandedDamage) + 1);

        if (weapons[count].name == NULL || weapons[count].type == NULL || weapons[count].damageType == NULL || weapons[count].damageDice == NULL || weapons[count].twoHandDamage == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            return;
        }

        // Copy the parsed strings into the dynamically allocated memory
        strcpy(weapons[count].name, tempName);
        strcpy(weapons[count].type, tempType);
        strcpy(weapons[count].damageType, tempDamageType);
        strcpy(weapons[count].damageDice, tempDamageDice);
        strcpy(weapons[count].twoHandDamage, tempTwoHandedDamage);

        // Populate the remaining fields
        weapons[count].isFinesse = tempIsFinesse;
        weapons[count].isVersatile = tempIsVersatile;
        weapons[count].isTwoHanded = tempIsTwoHanded;
        weapons[count].range[0] = range1;
        weapons[count].range[1] = range2;
        weapons[count].isLight = tempIsLight;
        weapons[count].isHeavy = tempIsHeavy;
        weapons[count].isReach = tempIsReach;

        count++;
    }

    fclose(file);

    if (count != 31) {
        fprintf(stderr, "Error: Expected %d weapons, but loaded %d.\n", 31, count);
    }
}

void freeWeapons(void) {
    for (int i = 0; i < 31; i++) {
        free(weapons[i].name);
        free(weapons[i].type);
        free(weapons[i].damageType);
        free(weapons[i].damageDice);
        free(weapons[i].twoHandDamage);
    }
}

void loadFilesTo2DArray(const char *filename, char **array, int i) {
    char buffer[256];
    int count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL && count < i) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Allocate memory for the string and copy it
        array[count] = malloc(strlen(buffer) + 1);
        if (array[count] == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            return;
        }
        strcpy(array[count], buffer);

        count++;
    }

    fclose(file);

    if (count != i) {
        fprintf(stderr, "Warning: Expected %d items, but loaded %d from %s.\n", i, count, filename);
    }
}

void free2DArray(char **array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL) {
            free(array[i]);
        }
    }
}

void loadClassesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char line[256];
    int class = 0;

    while (fgets(line, sizeof(line), file) != NULL && class < 12) {
        line[strcspn(line, "\n")] = '\0';  // Remove trailing newline if present

        char *token = strtok(line, ",");
        int subclass = 0;

        while (token != NULL && subclass < 5) {
            classes[class][subclass] = strdup(token);  // Allocate memory and copy the string
            if (classes[class][subclass] == NULL) {
                printf("Memory allocation failed for classes[%d][%d]\n", class, subclass);
                fclose(file);
                exit(1);
            }
            token = strtok(NULL, ",");
            subclass++;
        }

        class++;
    }

    fclose(file);
}

void freeClasses(void) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 5; j++) {
            free(classes[i][j]);  // Free allocated memory
        }
    }
}

// Function to load students from existing .txt files into the student list
void loadCharactersFromFile(struct Character **character) {
    FILE *index = fopen("index.txt", "r");
    if (index == NULL) {
        printf("Index file not found. No characters to load.\n\n");
        return;
    }

    char fileName[100];
    while (fgets(fileName, sizeof(fileName), index) != NULL) {
        // Remove trailing newline character
        fileName[strcspn(fileName, "\n")] = '\0';

        // Open each file and read character data
        FILE *characterFile = fopen(fileName, "r");
        if (characterFile == NULL) {
            printf("Could not open file: %s\n", fileName);
            continue;
        }

        struct Character *newCharacter = malloc(sizeof(struct Character));
        if (newCharacter == NULL) {
            printf("Memory allocation failed.\n");
            fclose(characterFile);
            exit(1);
        }

        // Allocate memory for nested structs
        newCharacter->class = malloc(sizeof(struct Class));
        newCharacter->armor = malloc(sizeof(struct Armor));
        newCharacter->weapon = malloc(sizeof(struct Weapon));
        if (!newCharacter->class || !newCharacter->armor || !newCharacter->weapon) {
            printf("Memory allocation failed for nested structs.\n");
            fclose(characterFile);
            free(newCharacter);
            exit(1);
        }

        char className[50], subClass[50], armorName[50], weaponName[50], background[50], race[50], alignment[50];

        // Read the character data from the file
        fscanf(characterFile,
               "Name: %[^\n]\n"
               "Level: %d\n"
               "Class: %[^\n]\n"
               "Subclass: %[^\n]\n"
               "Background: %[^\n]\n"
               "Race: %[^\n]\n"
               "Alignment: %[^\n]\n"
               "HP: %d\n"
               "Speed: %d\n"
               "Proficiency Modifier: %d\n"
               "Strength: %d\n"
               "Dexterity: %d\n"
               "Constitution: %d\n"
               "Intelligence: %d\n"
               "Wisdom: %d\n"
               "Charisma: %d\n"
               "Armor: %[^\n]\n"
               "Weapon: %[^\n]\n"
               "Shield: %d\n",
               newCharacter->name, &newCharacter->level, className, subClass, background, race, alignment, &newCharacter->HP,
               &newCharacter->speed, &newCharacter->proficiencyModifier, &newCharacter->strength, &newCharacter->dexterity, &newCharacter->constitution, 
               &newCharacter->intelligence, &newCharacter->wisdom, &newCharacter->charisma, armorName, weaponName, &newCharacter->hasShield);

        // Allocate memory for strings and copy the values
        newCharacter->class->name = malloc(strlen(className) + 1);
        strcpy(newCharacter->class->name, className);

        newCharacter->class->subClass = malloc(strlen(subClass) + 1);
        strcpy(newCharacter->class->subClass, subClass);

        strcpy(newCharacter->background, background);
        strcpy(newCharacter->race, race);
        strcpy(newCharacter->alignment, alignment);

        newCharacter->armor->name = malloc(strlen(armorName) + 1);
        strcpy(newCharacter->armor->name, armorName);

        newCharacter->weapon->name = malloc(strlen(weaponName) + 1);
        strcpy(newCharacter->weapon->name, weaponName);

        fclose(characterFile);

        // Add the character to the linked list
        newCharacter->next = *character;
        *character = newCharacter;
    }

    fclose(index);
    printf("Characters loaded successfully from files.\n");
}

void initializeGlobalArrays(void) {
    loadArmors("armors.txt");
    loadWeapons("weapons.txt");
    loadFilesTo2DArray("attributes.txt", attributes, 6);
    loadFilesTo2DArray("alignments.txt", alignments, 9);
    loadFilesTo2DArray("races.txt", races, 10);
    loadFilesTo2DArray("backgrounds.txt", backgrounds, 16);
    loadClassesFromFile("classes.txt");
}

// Armor functions
const char *armorRequirement(struct Armor *armor) {
    // Check specific strength requirements for heavy armor types

    if (strcmp(armor->name, "Chain Mail Armor") == 0) {
        return "13 Strength";
    } 
    else if (strcmp(armor->name, "Splint Armor") == 0 || strcmp(armor->name, "Plate Armor") == 0) {
        return "15 Strength";
    } 
    else {
        return " --------- "; // No strength requirement for other armors
    }
}

const char *armorStealth(struct Armor *armor) {
    return (armor->stealthDisadvantage == 1) ? "Disadvantage" : " --------- ";
}

// Weapon functions
const char *weaponFinesse(struct Weapon *weapon) {
    return (weapon->isFinesse == 1) ? "  Finesse  " : "Not Finesse";
}

const char *weaponVersatile(struct Weapon *weapon) {
    return (weapon->isVersatile == 1) ? "  Versatile  " : "Not Versatile";
}

const char *weaponRange(struct Weapon *weapon) {
    static char rangeStr[20]; // Use a static buffer for returning the string
    if (weapon->range[0] == 0 && weapon->range[1] == 0) {
        return "Melee";
    } 
    else {
        // Format the range into a string
        snprintf(rangeStr, sizeof(rangeStr), "%d/%d", weapon->range[0], weapon->range[1]);
        return rangeStr;
    }
}

//Selecting functions (adding/updating character data)
void selectName (struct Character *character) {
    int validInput = 0;
    char userName[25];

    inputBuffer();
    while (!validInput) {   
        printf("Enter your character's name: ");
        fgets(userName, 25, stdin); // Get user input
        userName[strcspn(userName, "\n")] = '\0';  // Check if the input has a newline character and remove it 
        validInput = isValidName(userName);
    }
    strcpy(character->name, userName);
    printf("\nYour character's name is: %s\n\n", character->name);
}

int selectLevel(struct Character *character) {
    int usersLevel, validInput = 0;

    while (!validInput) {
        printf("Enter your character's level (1-20): ");
        validInput = isValidInput(&usersLevel, 1, 20);  // Validate the input range
    }

    character->level = usersLevel;  // Set the character's level after validating

    printf("Your character is level: %d\n\n", character->level);
    return usersLevel;  // Output the selected level
}

void selectClass(struct Character *character){

    int usersClass;
    int validInput = 0;
    char tempClass[50], tempHitDie[50];

    if (character->class == NULL) {
        character->class = malloc(sizeof(struct Class));
        if (!character->class) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
    } 

    character->class->name = NULL;
    character->class->hitDie = NULL;
    
    // Display Class options
    printf("Enter your character's class:\n");
    for(int i = 0; i < 12; i++){
        printf("%d. %s\n", i + 1, classes[i][0]);
    }

    // Input validation loop
    while(!validInput){
        printf("Enter your Choice: ");
        validInput = isValidInput(&usersClass, 1, 12);  // Validate the input range
    }

    // Set class name
    strcpy(tempClass, classes[usersClass - 1][0]);
    if (character->class->name) {
        free(character->class->name); // Free old memory if allocated
    }
    character->class->name = malloc(strlen(tempClass) + 1);

    if (!character->class->name) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(character->class->name, tempClass);

    printf("You selected: %s\n\n", character->class->name);

    //adds hit die
    if(strcmp(character->class->name, "Wizard") == 0 || strcmp(character->class->name, "Sorcerer") == 0){
        strcpy(tempHitDie, "1D6");
    }
    else if(strcmp(character->class->name, "Bard") == 0 || strcmp(character->class->name, "Cleric") == 0 || strcmp(character->class->name, "Druid") == 0 || strcmp(character->class->name, "Monk") == 0 || strcmp(character->class->name, "Rogue") == 0 || strcmp(character->class->name, "Warlock") == 0){
        strcpy(tempHitDie, "1D8");
    }
    else if(strcmp(character->class->name, "Fighter") == 0 || strcmp(character->class->name, "Paladin") == 0 || strcmp(character->class->name, "Ranger") == 0){
        strcpy(tempHitDie, "1D10");
    }
    else if(strcmp(character->class->name, "Barbarian") == 0){
        strcpy(tempHitDie, "1D12");
    }
    else{
        strcpy(tempHitDie, "-1");
    }

    if (character->class->hitDie) {
        free(character->class->hitDie); // Free old memory if allocated
    }
    character->class->hitDie = malloc(strlen(tempHitDie) + 1);

    if (!character->class->hitDie) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(character->class->hitDie, tempHitDie);
}

void selectSubClass(struct Character *character){
    int usersSubClass, usersChoice = 0;
    int validInput = 0;
    int usersClass = -1;
    char tempSubClass[50];

    if(character->level < 3){
        printf("Reach level 3 to unlock Sub Classes.\n\n");
        strcpy(tempSubClass, "N/A");
        character->class->subClass = malloc(strlen(tempSubClass) + 1);
        strcpy(character->class->subClass, tempSubClass);
        return;
    }

    // Display sub class options
    printf("Enter your character's sub class:\n");
    
    // Display sub classes and finds users current class
    for(int i = 0; i < 13; i++){
        if(strcmp(character->class->name, classes[i][0]) == 0){
            for(int j = 1; j < 5; j++){
                usersClass = i;
                printf("%d. %s\n", j, classes[usersClass][j]);
            }
            break;
        }
    }
    
    // If users class is not found
    if (usersClass == -1) {
        printf("Error: Class not found. Please ensure your character's class is valid.\n");
        character->class->subClass = malloc(strlen("N/A") + 1);
        strcpy(character->class->subClass, "N/A");
        return;
    }

    // Input validation loop
    while(!validInput){
        printf("Enter your Choice: ");
        validInput = isValidInput(&usersChoice, 1, 4);  // Validate the input range
    }

    strcpy(tempSubClass, classes[usersClass][usersChoice]);
    if (character->class->subClass) {
        free(character->class->subClass); // Free old memory if allocated
    }
    character->class->subClass = malloc(strlen(tempSubClass) + 1);

    if (!character->class->subClass) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(character->class->subClass, tempSubClass);
    printf("You selected: %s\n\n", character->class->subClass);
}

void selectBackground(struct Character *character){
    int usersBackground;
    int validInput = 0;

    // Display background options
    printf("Enter your character's background:\n");
    for(int i = 0; i < 16; i++){
        printf("%d. %s\n", i + 1, backgrounds[i]);
    }

    // Input validation loop
    while(!validInput){
        printf("Enter your Choice: ");
        validInput = isValidInput(&usersBackground, 1, 16);  // Validate the input range
    }

    strcpy(character->background, backgrounds[usersBackground - 1]);
    printf("You selected: %s\n\n", character->background);
}

void selectRace(struct Character *character){
    int usersRace;
    int validInput = 0;

    // Display race options
    printf("Enter your characters race:\n");
    for(int i = 0; i < 10; i++){
        printf("%d. %s\n", i + 1, races[i]);
    }

    // Input validation loop
    while(!validInput){
        printf("Enter your Choice: ");
        validInput = isValidInput(&usersRace, 1, 10);  // Validate the input range
    }

    strcpy(character->race, races[usersRace - 1]);
    printf("You selected: %s\n\n", character->race);
}

void selectAlignment(struct Character *character){
    int usersAlignment;
    int validInput = 0;

    // Display alignment options
    printf("Enter your character's alignment:\n");
    for (int i = 0; i < 9; i++) {
        printf("%d. %s\n", i + 1, alignments[i]);
    }

    // Input validation loop
    while(!validInput){
        printf("Enter your Choice: ");
        validInput = isValidInput(&usersAlignment, 1, 9);  // Validate the input range
    }

    strcpy(character->alignment, alignments[usersAlignment - 1]);
    printf("You selected: %s\n\n", character->alignment);
}

void selectAttributes(struct Character *character){
    int userChoice;

    for(int i = 0; i < 6; i++){ 
        int validInput = 0;
        while(!validInput){
            printf("Enter your character's %s value (8-20): ", attributes[i]);
            validInput = isValidInput(&userChoice, 8, 20);  // Validate the input range
        }
        switch(i){
            case 0: 
                character->strength = userChoice;
                break;
            case 1: 
                character->dexterity = userChoice;
                break;
            case 2: 
                character->constitution = userChoice;
                break;
            case 3: 
                character->intelligence = userChoice;
                break;
            case 4: 
                character->wisdom = userChoice;
                break;
            case 5: 
                character->charisma = userChoice;
                break;
            default: 
                printf("Error in attribute selection.\n");
                return;
        }
        printf("Your character has %d %s!\n", userChoice, attributes[i]);
        validInput = 1;
    }
}
    
void selectArmor(struct Character *character) {
    int usersArmor;
    int validInput, strCheck = 0;
        // Display armor menu
        printf("Select Your Armor:\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("   %-22s |   %-6s |  %-3s | %-8s |    %-10s| %-15s\n", "Name", "Type", "AC", "Dex Mod.", "Stealth", "Requirements");
        printf("-------------------------------------------------------------------------------------\n");
        //prints armor from armors array
        for ( int i = 0; i < 9; i++) {
            printf("%d. %-22s |  %-7s |  %-3d |    %-5d | %-12s | %-15s\n", i + 1, armors[i].name, armors[i].type, armors[i].baseAC, calculateModifier(character->dexterity), armorStealth(&armors[i]), armorRequirement(&armors[i]));
        }
        for (int i = 9; i < 13; i++) {
            printf("%d. %-21s |  %-7s |  %-3d |    %-5d | %-12s | %-15s\n", i + 1, armors[i].name, armors[i].type, armors[i].baseAC, calculateModifier(character->dexterity), armorStealth(&armors[i]), armorRequirement(&armors[i]));
        }
        printf("-------------------------------------------------------------------------------------\n");
        
        do {
            printf("Enter your choice: ");
            validInput = isValidInput(&usersArmor, 1, 13);  // Validate the input range
            if (validInput) {  // Proceed only if the input is valid
                const char *requirement = armorRequirement(&armors[usersArmor - 1]);

                // Check strength requirement
                if ((strcmp(requirement, "13 Strength") == 0 && character->strength < 13) || (strcmp(requirement, "15 Strength") == 0 && character->strength < 15)) {
                    printf("\nYou do not have enough strength to wield this armor! Please try again.\n\n");
                    strCheck = 0;  // Reset flag
                } else {
                    strCheck = 1;  // Strength requirement satisfied
                }
            }
        } while (!validInput || !strCheck);

    // Assign selected armor
    character->armor = &armors[usersArmor - 1];
    printf("You selected: %s\n\n", character->armor->name);
}

void selectWeapon(struct Character *character){
    int usersWeapon;
    int validInput = 0;

        // Display weapon menu
        printf("Select Your Weapon(s):\n");
        printf("----------------------------------------------------------------------------------------------------------\n");
        printf(" %-19s |      %-9s |   %-10s | %-8s |    %-5s    |    %-5s    | %-10s \n", "Name", "Type", "DMG type", "DMG dice", "Finesse", "Versitile", "Range");
        printf("----------------------------------------------------------------------------------------------------------\n");
        //prints weapons from the weapons array
        for ( int i = 0; i < 9; i++) {
            printf("%d.  %-16s |  %-13s |  %-11s |    %-5s |   %-5s |  %-6s  | %-10s \n", i + 1, weapons[i].name, weapons[i].type, weapons[i].damageType, weapons[i].damageDice, weaponFinesse(&weapons[i]), weaponVersatile(&weapons[i]), weaponRange(&weapons[i]));
        }
        for (int i = 9; i < 31; i++) {
            printf("%d.  %-15s |  %-13s |  %-11s |    %-5s |   %-5s |  %-6s  | %-10s \n", i + 1, weapons[i].name, weapons[i].type, weapons[i].damageType, weapons[i].damageDice, weaponFinesse(&weapons[i]), weaponVersatile(&weapons[i]), weaponRange(&weapons[i]));
        }
        printf("----------------------------------------------------------------------------------------------------------\n");

        while (!validInput){
            printf("Enter your choice: ");
            validInput = isValidInput(&usersWeapon, 1, 31);  // Validate the input range
        }

    // Assign selected armor
    character->weapon = &weapons[usersWeapon - 1];
    printf("You selected: %s\n\n", character->weapon->name);
}

void selectShield(struct Character *character){
    int usersShield, validInput = 0; 

    printf("Is your character holding a shield? (1: yes | 0: no)\n");
    // Input validation loop
    while(!validInput){
        printf("Enter your Choice: ");
        validInput = isValidInput(&usersShield, 0, 1);  // Validate the input range
    }

    character->hasShield = usersShield;

    if(usersShield == 1){
        printf("Your character is now holding a shield!\n\n");
    }
    else{
        printf("Your character is not holding a shield!\n\n");
    }
}

// Calculate functions
// Returns the modifer associated with your character attribute
int calculateModifier(int attribute){
    return (attribute - 10) / 2;
}

// Returns your characters armor class number
int calculateArmorClass(int dexterity, const char *armorName, int hasShield) {
    int shieldBonus = hasShield ? 2 : 0;            // +2 AC if the character has a shield
    int maxDex = 0;                                 // Default max dex modifier

    // Find the armor in the armors array
    struct Armor *selectedArmor = NULL;
    for (int i = 0; i < sizeof(armors) - 1; i++) {
        if (strcmp(armors[i].name, armorName) == 0) {
            selectedArmor = &armors[i];
            break;
        }
    }
    // If armor is not found, return a default value
    if (!selectedArmor) {
        printf("Invalid armor type: %s\n", armorName);
        return 10; // Default unarmored AC
    }

    // Apply max dexterity bonus if required
    if (selectedArmor->requiresDexCap == 1 && calculateModifier(dexterity) > selectedArmor->maxDexBonus) {
        maxDex = selectedArmor->maxDexBonus;
    }
    if(selectedArmor->maxDexBonus == -1){
        maxDex = calculateModifier(dexterity);
    }
    //if the armor is of "Heavy" type then AC gets 0 dexterity bonus
    if(strcmp(selectedArmor->type, "Heavy") == 0){
        maxDex = 0;
    }

    // Calculate the final AC
    int armorClass = selectedArmor->baseAC + maxDex + shieldBonus;
    return armorClass;
}

int calculateRollModifier(struct Character *head, char *diceCharacterName, int numChoice){
    //puts all characters modifiers in an array
    int *attributes[] = {
        &head->strength, &head->dexterity,
        &head->constitution, &head->intelligence,
        &head->wisdom, &head->charisma
    };  
    //check to see if list is empty
    if(head == NULL){ 
        return -1; //indicates error
    }
    //checks to make sure the character entered exists
    if (strcmp(head->name, diceCharacterName) != 0){
        return -1; //not found -1 indicating error
    }
    //validates numChoice
    if(numChoice > 6 || numChoice < 1){
        return rollD20();
    }
    //returns the baseRoll + your character modifier of choice
    return rollD20() + calculateModifier(*attributes[numChoice - 1]);
}

int calculateDamageDiceRoll(struct Weapon *weapon){

    if (!weapon || !weapon->damageDice){
            return -1; // Error: Null pointer
        }

        if (strcasecmp(weapon->damageDice, "1D4") == 0){
            return rollD4();
        } 
        else if (strcasecmp(weapon->damageDice, "1D6") == 0){
            return rollD6();
        } 
        else if (strcasecmp(weapon->damageDice, "1D8") == 0){
            return rollD8();
        } 
        else if (strcasecmp(weapon->damageDice, "1D10") == 0){
            return rollD10();
        } 
        else if (strcasecmp(weapon->damageDice, "1D12") == 0){
            return rollD12();
        } 
        else if (strcasecmp(weapon->damageDice, "2D6") == 0){
            return rollD6() + rollD6();
        } 
        else{
            return -1; // Error: Unknown dice type
        }
}

int calculateDamageRoll(struct Character *character, char *characterName) {
    int dmgDice;

    // Check if character or characterName is NULL
    if (character == NULL || characterName == NULL) {
        return -1; // Error case
    }

    // Check if the character name matches
    if (strcmp(character->name, characterName) == 0) {
        // Ensure weapon is not NULL
        if (character->weapon != NULL) {
            struct Weapon *weapon = character->weapon;

            // Handle finesse property
            if (weapon->isFinesse == 1) {
                dmgDice = calculateDamageDiceRoll(weapon) + calculateModifier(character->dexterity);
            }
            // Handle versatile property
            else if (weapon->isVersatile == 1){
                if (character->hasShield == 0){
                    // Use two-handed damage dice
                    dmgDice = calculateDamageDiceRoll(weapon) + calculateModifier(character->strength);
                } 
                else {
                    // Use standard one-handed damage dice
                    dmgDice = calculateDamageDiceRoll(weapon) + calculateModifier(character->strength);
                }
            }
            // Handle standard strength-based attacks
            else {
                dmgDice = calculateDamageDiceRoll(weapon) + calculateModifier(character->strength);
            }
        } 
        else {
            return -1; // Weapon is NULL
        }
    } 
    else {
        return -1; // Character name does not match
    }

    return dmgDice; // Return damage dealt
}

int calculateAttackRoll(struct Character *character, char *characterName){

    if (character == NULL || characterName == NULL || character->weapon == NULL) {
        return -1; // Error case
    }

    // Base roll
    int baseRoll = rollD20();
    int abilityModifier;
    int isProficient = character->proficiencyModifier;

    // Determine which ability modifier to use
    if (character->weapon->isFinesse == 1 || strcmp(character->weapon->type, "Ranged") == 0 || (strcmp(character->weapon->type, "Melee/Ranged") == 0 && character->weapon->isFinesse == 1)) {
        abilityModifier = character->dexterity;
    } 
    else {
        abilityModifier = character->strength;
    }

    // Calculate and return the attack roll
    return baseRoll + calculateModifier(abilityModifier) + isProficient;
}

int calculateHealth(struct Character *character){

    int conMod = calculateModifier(character->constitution);
    int charLVL = character->level;

    if (!character || !character->class || !character->class->hitDie) {
        printf("Error: Invalid character or class data.\n");
        return -1; // Error
    }

    if(strcmp(character->class->hitDie, "1D6") == 0){
        return (6 + conMod) + (4 * charLVL) + (conMod * charLVL);
    }
    else if(strcmp(character->class->hitDie, "1D8") == 0){
        return (8 + conMod) + (5 * charLVL) + (conMod * charLVL);
    }
    else if(strcmp(character->class->hitDie, "1D10") == 0){
        return (10 + conMod) + (6 * charLVL) + (conMod * charLVL);
    }
    else if(strcmp(character->class->hitDie, "1D12") == 0){
        return (12 + conMod) + (7 * charLVL) + (conMod * charLVL);
    }
    else{
        return -1; // Error
    }
}

int calculateProficiencyModifier(struct Character *character){
    return ((character->level - 1) / 4) + 2;
}

// Display functions
void addCharacter(struct Character **newChar){
    int userCurrLevel;
    //make space for new character in memory
    struct Character *newCharacter = malloc(sizeof(struct Character));
    if (newCharacter == NULL){
        printf("Failed to allocate memory :(\n");
        exit(1);
    }
    
    newCharacter->class = malloc(sizeof(struct Class));
    if (newCharacter->class == NULL) {
        printf("Failed to allocate memory for class.\n");
        free(newCharacter);
        exit(1);
    }

    newCharacter->armor = malloc(sizeof(struct Armor));
    if (newCharacter->armor == NULL) {
        printf("Failed to allocate memory for armor.\n");
        free(newCharacter->class);
        free(newCharacter);
        exit(1);
    }

    newCharacter->weapon = malloc(sizeof(struct Weapon));
    if (newCharacter->weapon == NULL) {
        printf("Failed to allocate memory for weapon.\n");
        free(newCharacter->armor);
        free(newCharacter->class);
        free(newCharacter);
        exit(1);
    }

    strcpy(newCharacter->background, "N/A");
    strcpy(newCharacter->race, "N/A");
    strcpy(newCharacter->alignment, "N/A");
    newCharacter->level = 1; // Default level
    newCharacter->hasShield = 0; // Default to no shield
    newCharacter->speed = 30;
    newCharacter->proficiencyModifier = 0;
    newCharacter->HP = 0;
    
    //prompt user to enter details for character
    printf("For more information regarding DnD character details visit DnD Beyond\n\n");

    // Calls the select functions to gather information about your character
    selectName(newCharacter);
    userCurrLevel = selectLevel(newCharacter);
    selectClass(newCharacter); 
    selectSubClass(newCharacter);
    selectBackground(newCharacter);
    selectRace(newCharacter);
    selectAlignment(newCharacter);
    selectAttributes(newCharacter);
    selectArmor(newCharacter);
    selectWeapon(newCharacter);
    selectShield(newCharacter);
    newCharacter->proficiencyModifier = calculateProficiencyModifier(newCharacter);
    newCharacter->HP = calculateHealth(newCharacter);
    //inserts the new character at the beginning of the list
    newCharacter->next = *newChar;
    *newChar = newCharacter;

    // Gets character first name or name before any spaces
    char firstName[100];
    sscanf(newCharacter->name, "%s", firstName);
    // Create a dynamic file name
    char fileName[100];
    snprintf(fileName, sizeof(fileName), "%s.txt", firstName);

    // Write character details to the file
    FILE *characterFile = fopen(fileName, "w");
    if (characterFile == NULL) {
        printf("Couldn't open the file: %s\n", fileName);
    } else {
        fprintf(characterFile, "Name: %s\n", newCharacter->name);
        fprintf(characterFile, "Level: %d\n", newCharacter->level);
        fprintf(characterFile, "Class: %s\n", newCharacter->class->name);
        fprintf(characterFile, "Subclass: %s\n", newCharacter->class->subClass);
        fprintf(characterFile, "Background: %s\n", newCharacter->background);
        fprintf(characterFile, "Race: %s\n", newCharacter->race);
        fprintf(characterFile, "Alignment: %s\n", newCharacter->alignment);
        fprintf(characterFile, "HP: %d\n", newCharacter->HP);
        fprintf(characterFile, "Speed: %d\n", newCharacter->speed);
        fprintf(characterFile, "Proficiency Modifier: %d\n", newCharacter->proficiencyModifier);
        fprintf(characterFile, "Strength: %d\n", newCharacter->strength);
        fprintf(characterFile, "Dexterity: %d\n", newCharacter->dexterity);
        fprintf(characterFile, "Constitution: %d\n", newCharacter->constitution);
        fprintf(characterFile, "Intelligence: %d\n", newCharacter->intelligence);
        fprintf(characterFile, "Wisdom: %d\n", newCharacter->wisdom);
        fprintf(characterFile, "Charisma: %d\n", newCharacter->charisma);
        fprintf(characterFile, "Armor: %s\n", newCharacter->armor->name);
        fprintf(characterFile, "Weapon: %s\n", newCharacter->weapon->name);
        fprintf(characterFile, "Shield: %d", newCharacter->hasShield);
        printf("Character data saved successfully to %s.\n", fileName);
        fclose(characterFile);

        // Append the file name to index.txt
        FILE *index = fopen("index.txt", "a");
        if (index == NULL) {
            printf("Couldn't open the index file.\n");
        } 
        else {
            fprintf(index, "%s\n", fileName);
            fclose(index);
        }
    }
}

void displayCharacter(struct Character *character){

    //check to see if list is empty
    if(character == NULL){ 
        printf("\nNo characters in the list...\n");
        printf("Please enter a character first\n\n");
        return;
    }

    //displays all charcters
    printf("List of characters:\n\n");
    while(character != NULL){
        printf("    ___________ Name: %s ___________\n\n", character->name);
        printf("Class: %s   Level: %d   Background: %s\n\n", character->class->name, character->level, character->background);                                    //displays Class, Level, Background
        printf("Sub Class: %s   Race: %s    Alignment: %s\n\n", character->class->subClass, character->race, character->alignment);                                                                //displays Race, Alignment
        printf("Armor: %s   Armor Class: %d     Weapon: %s\n\n", character->armor->name, calculateArmorClass(character->dexterity, character->armor->name, character->hasShield), character->weapon->name);   //displays Armor, Armor Class, Weapon
        printf("Total HP: %d    Proficiency Modifier: %d\n\n", character->HP, character->proficiencyModifier);
        printf("Strength\nAbility Score: %d\nModifier: %d\n\n", character->strength, calculateModifier(character->strength));                          //displays Strength
        printf("Dexterity\nAbility Score: %d\nModifier: %d\n\n", character->dexterity, calculateModifier(character->dexterity));                       //displays Dexterity 
        printf("Constitution\nAbility Score: %d\nModifier: %d\n\n", character->constitution, calculateModifier(character->constitution));              //displays Constitution
        printf("Intelligence\nAbility Score: %d\nModifier: %d\n\n", character->intelligence, calculateModifier(character->intelligence));              //displays Intelligence
        printf("Wisdom\nAbility Score: %d\nModifier: %d\n\n", character->wisdom, calculateModifier(character->wisdom));                                //displays Wisdom
        printf("Charisma\nAbility Score: %d\nModifier: %d\n\n", character->charisma, calculateModifier(character->charisma));                          //displays Charisma
        character = character->next;
    }
}

//Searches for a character by name
void searchCharacter(struct Character *character, char *searchCharacterName){
    int ifFound = 0;

    while(character != NULL){
        if (strcmp(character->name, searchCharacterName) == 0){
            printf("    ___________ Name: %s ___________\n\n", character->name);
            printf("Class: %s   Level: %d   Background: %s\n\n", character->class->name, character->level, character->background);                                    //displays Class, Level, Background
            printf("Sub Class: %s   Race: %s    Alignment: %s\n\n", character->class->subClass, character->race, character->alignment);                                                                //displays Race, Alignment
            printf("Armor: %s   Armor Class: %d     Weapon: %s\n\n", character->armor->name, calculateArmorClass(character->dexterity, character->armor->name, character->hasShield), character->weapon->name);   //displays Armor, Armor Class, Weapon
            printf("Total HP: %d    Proficiency Modifier: %d\n\n", character->HP, character->proficiencyModifier);
            printf("Strength\nAbility Score: %d\nModifier: %d\n\n", character->strength, calculateModifier(character->strength));                          //displays Strength
            printf("Dexterity\nAbility Score: %d\nModifier: %d\n\n", character->dexterity, calculateModifier(character->dexterity));                       //displays Dexterity 
            printf("Constitution\nAbility Score: %d\nModifier: %d\n\n", character->constitution, calculateModifier(character->constitution));              //displays Constitution
            printf("Intelligence\nAbility Score: %d\nModifier: %d\n\n", character->intelligence, calculateModifier(character->intelligence));              //displays Intelligence
            printf("Wisdom\nAbility Score: %d\nModifier: %d\n\n", character->wisdom, calculateModifier(character->wisdom));                                //displays Wisdom
            printf("Charisma\nAbility Score: %d\nModifier: %d\n\n", character->charisma, calculateModifier(character->charisma));
            ifFound = 1;
            break;
        }
        character = character->next;
    }

    if(ifFound != 1){
        printf("\nYour character could not found :(\n\n");
    }
}

//Updates details of your character
void updateCharacter(struct Character *updatedCharacter, char *updateCharacterName){

    while (updatedCharacter != NULL){
        if (strcmp(updatedCharacter->name, updateCharacterName) == 0){
            printf("Enter updated details for your character: %s:\n", updateCharacterName);

            selectLevel(updatedCharacter);
            selectClass(updatedCharacter);
            selectBackground(updatedCharacter);
            selectRace(updatedCharacter);
            selectAlignment(updatedCharacter);
            selectAttributes(updatedCharacter); 
            selectArmor(updatedCharacter);
            selectWeapon(updatedCharacter);
            selectShield(updatedCharacter);

            printf("Character details have been updated successfully.\n\n");
            return;
        }
        updatedCharacter = updatedCharacter->next;
    }

    printf("Character could not be found :( \n\n");
}

//Deletes a character from the list
void deleteCharacter(struct Character **character, char *deleteCharacterName){
    struct Character *prev = NULL;

    struct Character *temp = *character;

    while(temp != NULL && strcmp(temp->name, deleteCharacterName) != 0){
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL){
        printf("Your character could not be found :(\n\n");
        return;
    }

    if(prev == NULL){
        *character = temp->next;
    } 
    else{
        prev->next = temp->next;
    }

    free(temp);
    printf("\nYour character has been deleted...\n\n");
}

void levelUpCharacter(struct Character *character, char *levelCharacterName){
    int userChoice;
    int validInput = 0;
    if (strcmp(character->name, levelCharacterName) == 0){
        printf("Are you sure you want to level up '%s'?\n", character->name);
        printf("1. Yes\n");
        printf("2. No\n");
        
        while(!validInput){
            printf("Enter your Choice: ");
            scanf("%d", &userChoice);

            if(userChoice != 1 && userChoice != 2) {
                printf("Invalid choice, please try again...\n\n");
            } 
            else{
                validInput = 1;
            }
        }
    if(userChoice == 1){
        character->level++;
        printf("\n'%s' has leveled up! New level: %d\n\n", character->name, character->level);
        character->HP = calculateHealth(character);
        if(character->level == 3){
            printf("You have reached level 3! It's time to choose a subclass for '%s'.\n", character->name);
            selectSubClass(character);
        }
        character->proficiencyModifier = calculateProficiencyModifier(character);
        return;
    }
    }
    else{
        printf("Error: Character not found...\n\n");
    }
}

void getCharacterName(char *name, const char *prompt) {
    inputBuffer();
    printf("%s", prompt);
    fgets(name, 25, stdin);
    name[strcspn(name, "\n")] = '\0';
}

// Dice rolling functions
//generates a random number between 1 & 20
int rollD20(void){
    return rand() % 20 + 1;
}
//generates a random number between 1 & 12
int rollD12(void){
    return rand() % 12 + 1;
}
//generates a random number between 1 & 10
int rollD10(void){
    return rand() % 10 + 1;
}
//generates a random number between 1 & 8
int rollD8(void){
    return rand() % 8 + 1;
}
//generates a random number between 1 & 6
int rollD6(void){
    return rand() % 6 + 1;
}
//generates a random number between 1 & 4
int rollD4(void){
    return rand() % 4 + 1;
}