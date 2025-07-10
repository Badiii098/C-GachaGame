#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COMMON 50
#define RARE 30
#define EPIC 15
#define LEGENDARY 5

#define MAX_COMMON 300
#define MAX_RARE 200
#define MAX_EPIC 100
#define MAX_LEGENDARY 10

const char* getGachaItem() {
    int roll = rand() % 100 + 1;

    if (roll <= LEGENDARY) {
        return "Legendary Item";
    } else if (roll <= LEGENDARY + EPIC) {
        return "Epic Item";
    } else if (roll <= LEGENDARY + RARE) {
        return "Rare Item";
    } else {
        return "Common Item";
    }
}

void shuffleBoxes(const char* boxes[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        const char* temp = boxes[i];
        boxes[i] = boxes[j];
        boxes[j] = temp;
    }
}

void printLineSeparator() {
    printf("==========================================\n");
}

void printHeader(const char* title) {
    printLineSeparator();
    printf("               %s\n", title);
    printLineSeparator();
}

void saveInventory(int* inventory) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error membuka file untuk menyimpan inventory.\n");
        return;
    }
    fprintf(file, "%d %d %d %d\n", inventory[0], inventory[1], inventory[2], inventory[3]);
    fclose(file);
    printf("Inventory telah disimpan.\n");
}

void loadInventory(int* inventory) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Tidak ada file inventory yang ditemukan, memulai dengan inventory kosong.\n");
        return;
    }
    fscanf(file, "%d %d %d %d", &inventory[0], &inventory[1], &inventory[2], &inventory[3]);
    fclose(file);
    printf("Inventory telah dimuat.\n");
}

void checkForCompletion(int* inventory) {
    if (inventory[3] >= MAX_LEGENDARY) {
        printf("Selamat! Anda telah menemukan 10 Legendary Items dan menamatkan permainan!\n");
        saveInventory(inventory);
        exit(0);
    }
}

void playGacha(int* inventory) {
    printHeader("Gacha Game");

    const char* boxes[3];
    int commonCount = 0;
    int rareCount = 0;
    int epicCount = 0;
    int legendaryCount = 0;
    int totalOpens = 0;
    int selection;

    while (totalOpens < 10) {
        for (int i = 0; i < 3; i++) {
            boxes[i] = getGachaItem();
        }

        printf("\nPilih kotak untuk dibuka (1-3) atau 0 untuk kembali ke menu utama: ");
        scanf("%d", &selection);

        if (selection == 0) {
            printf("Kembali ke menu utama.\n\n");
            break;
        }

        if (selection < 1 || selection > 3) {
            printf("Pilihan tidak valid. Harap pilih angka antara 0 dan 3.\n");
            continue;
        }

        totalOpens++;
        const char* item = boxes[selection - 1];
        printf("Anda membuka kotak %d dan menemukan: %s\n", selection, item);

        if (item == "Common Item") {
            commonCount++;
            inventory[0]++;
            if (commonCount >= MAX_COMMON) {
                printf("Anda telah memperoleh %d Common Items. Program berakhir.\n", commonCount);
                break;
            }
        } else if (item == "Rare Item") {
            rareCount++;
            inventory[1]++;
            if (rareCount >= MAX_RARE) {
                printf("Anda telah memperoleh %d Rare Items. Program berakhir.\n", rareCount);
                break;
            }
        } else if (item == "Epic Item") {
            epicCount++;
            inventory[2]++;
            if (epicCount >= MAX_EPIC) {
                printf("Anda telah memperoleh %d Epic Items. Program berakhir.\n", epicCount);
                break;
            }
        } else if (item == "Legendary Item") {
            legendaryCount++;
            inventory[3]++;
            if (legendaryCount >= MAX_LEGENDARY) {
                printf("Selamat! Anda telah menemukan 10 Legendary Items dan menamatkan permainan!\n");
                saveInventory(inventory);
                exit(0);
            }
        }

        if (totalOpens >= 10) {
            printf("Anda telah membuka 10 kotak. Kembali ke menu utama.\n\n");
            break;
        }

        shuffleBoxes(boxes, 3);
    }

    printf("\nRingkasan Game:\n");
    printf("Total kotak yang dibuka: %d\n", totalOpens);
    printf("Common Items: %d\n", commonCount);
    printf("Rare Items: %d\n", rareCount);
    printf("Epic Items: %d\n", epicCount);
    printf("Legendary Items: %d\n", legendaryCount);
    printf("\n");
}

void displayInventory(int* inventory) {
    printHeader("Inventory");
    printf("Common Items: %d\n", inventory[0]);
    printf("Rare Items: %d\n", inventory[1]);
    printf("Epic Items: %d\n", inventory[2]);
    printf("Legendary Items: %d\n", inventory[3]);
    printf("\n");
    checkForCompletion(inventory);
}

void craftItems(int* inventory) {
    int choice;
    while (1) {
        printHeader("Crafting Menu");
        printf("1. Craft 5 Common Items into 1 Rare Item\n");
        printf("2. Craft 5 Rare Items into 1 Epic Item\n");
        printf("3. Craft 5 Epic Items into 1 Legendary Item\n");
        printf("0. Kembali ke menu utama\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 0) {
            printf("Kembali ke menu utama.\n\n");
            break;
        }

        switch (choice) {
            case 1:
                if (inventory[0] >= 5) {
                    inventory[0] -= 5;
                    inventory[1]++;
                    printf("Anda berhasil meng-craft 5 Common Items menjadi 1 Rare Item!\n\n");
                } else {
                    printf("Tidak cukup Common Items untuk crafting.\n\n");
                }
                break;
            case 2:
                if (inventory[1] >= 5) {
                    inventory[1] -= 5;
                    inventory[2]++;
                    printf("Anda berhasil meng-craft 5 Rare Items menjadi 1 Epic Item!\n\n");
                } else {
                    printf("Tidak cukup Rare Items untuk crafting.\n\n");
                }
                break;
            case 3:
                if (inventory[2] >= 5) {
                    inventory[2] -= 5;
                    inventory[3]++;
                    printf("Anda berhasil meng-craft 5 Epic Items menjadi 1 Legendary Item!\n\n");
                } else {
                    printf("Tidak cukup Epic Items untuk crafting.\n\n");
                }
                break;
            default:
                printf("Pilihan tidak valid.\n\n");
                break;
        }
        checkForCompletion(inventory);
    }
}

void displayHowToPlay() {
    printHeader("How to Play");
    printf("Tujuan dari permainan ini adalah untuk mendapatkan 10 Legendary Items.\n\n");
    printf("1. Gacha Game: Anda bisa membuka kotak untuk mendapatkan item secara acak.\n");
    printf("   - Common Item: 50%% kemungkinan\n");
    printf("   - Rare Item: 30%% kemungkinan\n");
    printf("   - Epic Item: 15%% kemungkinan\n");
    printf("   - Legendary Item: 5%% kemungkinan\n\n");
    printf("2. Inventory: Menampilkan jumlah masing-masing jenis item yang Anda miliki.\n\n");
    printf("3. Craft Items: Anda dapat meng-craft item untuk mendapatkan item yang lebih langka.\n");
    printf("   - Craft 5 Common Items menjadi 1 Rare Item\n");
    printf("   - Craft 5 Rare Items menjadi 1 Epic Item\n");
    printf("   - Craft 5 Epic Items menjadi 1 Legendary Item\n\n");
    printf("4. How to Play: Akan membuka opsi cara bermain game gacha\n\n");
    printf("0. Save And Exit: Akan menghentikan program dan otomatis menyimpan inventory anda\n\n");
    printf("Selamat bermain dan semoga beruntung!\n\n");
}

int main() {
    srand(time(NULL));

    int choice;
    char confirmation[4];
    int inventory[4] = {0, 0, 0, 0};  // [common, rare, epic, legendary]

    loadInventory(inventory);

    while (1) {
        printHeader("Menu Utama");
        printf("1. Gacha Game\n");
        printf("2. Inventory\n");
        printf("3. Craft Items\n");
        printf("4. How to Play\n");
        printf("0. Save And Exit\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                printf("Apakah Anda yakin ingin bermain Gacha Game? (yes/no): ");
                scanf("%s", confirmation);
                printf("\n");
                if (strcmp(confirmation, "yes") == 0) {
                    playGacha(inventory);
                } else {
                    printf("Kembali ke menu.\n\n");
                }
                break;
            case 2:
                displayInventory(inventory);
                break;
            case 3:
                craftItems(inventory);
                break;
            case 4:
                displayHowToPlay();
                break;
            case 0:
                saveInventory(inventory);
                printf("Keluar dari program. Sampai jumpa!\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Harap masukkan 1, 2, 3, 4, atau 0.\n\n");
        }
    }

    return 0;
}
