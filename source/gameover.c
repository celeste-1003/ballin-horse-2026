
#include "cprocessing.h"
#include <stdio.h>

#include "header/gameover.h"
#include "header/assets.h"
#include "header/draw.h"
#include "header/constants.h"

// Total number of possible win ranks and lose screens
#define RANK_COUNT 7
#define LOSE_COUNT 2

// Initialising variables
int course_par = 3;
int stroke_count = 0;
int lose_type = 0;

// Top text for each win rank
const char* rank_top[RANK_COUNT] = {
    "I am proud of you",
    "A-neigh-zing",
    "*Sniff* *Sniff*",
    "Nehhh",
    "*Bombastic side eye*",
    "Neigh-I-say",
    "Absolute Horsepoop"
};

// Bottom text for each win rank 
const char* rank_bottom[RANK_COUNT] = {
    "The horse gods applaud you",
    "The horse gods are appeased",
    "The horse gods are watching",
    "The horse gods are unimpressed",
    "The horse gods are questioning you",
    "The horse gods are not amused",
    "The horse gods have left the chat"
};

// WIN SCREEN IMAGES
const char* rank_image_paths[RANK_COUNT] = {
    "Assets/sprites/rank_0.jpg",
    "Assets/sprites/rank_1.jpg",
    "Assets/sprites/rank_2.jpg",
    "Assets/sprites/rank_3.jpg",
    "Assets/sprites/rank_4.jpg",
    "Assets/sprites/rank_5.jpg",
    "Assets/sprites/rank_6.jpg"
};

// Stores the loaded win images
CP_Image rank_images[RANK_COUNT] = { 0 };

// Different text for the two lose conditions
const char* lose_titles[LOSE_COUNT] = {
    "You drowned.",
    "You got spiked."
};

const char* lose_subtitles[LOSE_COUNT] = {
    "How dare you...",
    "Ouch. That looks painful..."
};

// Background image for each lose screen
const char* lose_image_paths[LOSE_COUNT] = {
    "Assets/sprites/lose_water.png",
    "Assets/sprites/lose_spike.png"
};

// Stores the loaded lose images
CP_Image lose_images[LOSE_COUNT] = { 0 };

// Prevents loading the same images multiple times
int images_loaded = 0;

// GAMEOVER INITIALISATION
void gameover_init(void) {

    // Skip loading if the images are already available
    if (images_loaded) {
        return;
    }

    // Load the seven win images
    for (int i = 0; i < RANK_COUNT; i++) {
        rank_images[i] = CP_Image_Load(rank_image_paths[i]);
    }

    // Load the two lose background images
    for (int i = 0; i < LOSE_COUNT; i++) {
        lose_images[i] = CP_Image_Load(lose_image_paths[i]);
    }

    // Remember that loading has been completed
    images_loaded = 1;
}

void gameover_set_results(int par, int strokes) {
    // Store the course par and number of strokes
    course_par = par;
    stroke_count = strokes;
}

void gameover_set_lose(int type) {
    // Ensure the index is within the two available lose screens
    if (type >= 0 && type < LOSE_COUNT) {
        lose_type = type;
    }
    else {
        lose_type = 0;
    }
}

int get_gameover_rank(void) {

    // Negative = under par, positive = over par
    int difference = stroke_count - course_par;
    // Hole-in-one receives the highest rank
    if (stroke_count == 1) {
        return 0;
    }
    // Two or more strokes below par
    if (difference <= -2) {
        return 1;
    }
    // One stroke below par
    if (difference == -1) {
        return 2;
    }
    // Exactly equal to par
    if (difference == 0) {
        return 3;
    }
    // One stroke above par
    if (difference == 1) {
        return 4;
    }
    // Two strokes above par
    if (difference == 2) {
        return 5;
    }
    // Three or more strokes above par
    return 6;
}


// Reuses draw_text() while adding a rotation angle
void draw_gameover_text(
    CP_Font font,
    CP_Color col,
    CP_TEXT_ALIGN_HORIZONTAL h,
    CP_TEXT_ALIGN_VERTICAL v,
    const char* text,
    float x,
    float y,
    float rotation
) {

    // Save drawing settings before changing coordinates
    CP_Settings_Save();

    // Move the origin to the text position
    CP_Settings_Translate(x, y);

    // Rotate the drawing coordinates
    CP_Settings_Rotate(rotation);

    // Draw at the new origin
    draw_text(
        font, col, h, v,
        text, 0.0f, 0.0f
    );

    // Restore settings so subsequent objects are unaffected
    CP_Settings_Restore();
}


void draw_win_screen(void) {

    // Buffers for formatting the par and stroke values as text
    char par_text[50];
    char strokes_text[50];
    char difference_text[50];

    // Determine the player's performance and rank
    int difference = stroke_count - course_par;
    int rank = get_gameover_rank();

    // Colours for the popup and text
    CP_Color panel_col = CP_Color_Create(42, 45, 48, 255);
    CP_Color green_col = CP_Color_Create(119, 205, 84, 255);
    CP_Color yellow_col = CP_Color_Create(240, 225, 140, 255);

    // Save drawing settings
    CP_Settings_Save();

    // Rectangles use their top-left corner as their position
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_NoStroke();

    // Darken the existing course while keeping it visible
    draw_rect(
        0.0f, 0.0f,
        (float)SCREEN_WIDTH,
        (float)SCREEN_HEIGHT,
        CP_Color_Create(0, 0, 0, 180)
    );

    // Main win popup, 1100 x 650
    draw_rect(
        250.0f, 125.0f,
        1100.0f, 650.0f,
        panel_col
    );

    // Display the Stage Clear title
    CP_Settings_TextSize(85.0f);

    draw_text(
        title_font, green_col,
        CP_TEXT_ALIGN_H_CENTER,
        CP_TEXT_ALIGN_V_MIDDLE,
        "STAGE CLEAR",
        800.0f, 205.0f
    );

    // Separate the score section from the rank section
    draw_rect(
        790.0f, 290.0f,
        5.0f, 420.0f,
        White
    );

    // Convert the par value into a string
    sprintf_s(
        par_text, sizeof(par_text),
        "Course Par: %d", course_par
    );

    // Convert the stroke count into a string
    sprintf_s(
        strokes_text, sizeof(strokes_text),
        "Your Strokes: %d", stroke_count
    );

    CP_Settings_TextSize(36.0f);

    // Centre of the left panel
    float left_center_x = (250.0f + 790.0f) / 2.0f;

    // Display the course par
    draw_text(
        body_font, White,
        CP_TEXT_ALIGN_H_CENTER,
        CP_TEXT_ALIGN_V_MIDDLE,
        par_text,
        left_center_x, 320.0f
    );

    // Display the number of strokes
    draw_text(
        body_font, White,
        CP_TEXT_ALIGN_H_CENTER,
        CP_TEXT_ALIGN_V_MIDDLE,
        strokes_text,
        left_center_x, 390.0f 
    );


    // Format the difference between strokes and par
    if (difference < 0) {
        // Fewer strokes than par is a better result
        sprintf_s(
            difference_text, sizeof(difference_text),
            "%d Under Par", -difference
        );
    }
    else if (difference > 0) {
        // More strokes than par
        sprintf_s(
            difference_text, sizeof(difference_text),
            "%d Over Par", difference
        );
    }
    else {
        // Strokes are exactly equal to par
        sprintf_s(
            difference_text, sizeof(difference_text),
            "Even Par"
        );
    }

    CP_Settings_TextSize(42.0f);

    // Draw the formatted par difference
    draw_text(
        title_font, yellow_col,
        CP_TEXT_ALIGN_H_CENTER,
        CP_TEXT_ALIGN_V_MIDDLE,
        difference_text,
        left_center_x, 460.0f
    );

    CP_Settings_TextSize(46.0f);

    // Select and rotate the top rank text
    draw_gameover_text(
        title_font, White,
        CP_TEXT_ALIGN_H_CENTER,
        CP_TEXT_ALIGN_V_MIDDLE,
        rank_top[rank],
        1070.0f, 340.0f,
        -5.0f
    );

    // Position the rank image using its centre
    CP_Settings_ImageMode(CP_POSITION_CENTER);

    // Get the image's original dimensions
    float image_width = (float)CP_Image_GetWidth(rank_images[rank]); 
    float image_height = (float)CP_Image_GetHeight(rank_images[rank]);

    // Maximum size the image can occupy
    float max_width = 340.0f;
    float max_height = 260.0f;

    // Calculate scale factors
    float scale_x = max_width / image_width;
    float scale_y = max_height / image_height;

    // Use the smaller scale to preserve the aspect ratio
    float scale = scale_x < scale_y ? scale_x : scale_y;

    // Draw image centred at (1070, 510)
    CP_Settings_ImageMode(CP_POSITION_CENTER);

    draw_image(
        rank_images[rank],
        1070.0f, 510.0f,
        image_width * scale,
        image_height * scale,
        255
    );

    CP_Settings_TextSize(55.0f);

    // Select and rotate the bottom rank text
    draw_gameover_text(
        title_font, yellow_col,
        CP_TEXT_ALIGN_H_CENTER,
        CP_TEXT_ALIGN_V_MIDDLE,
        rank_bottom[rank],
        1070.0f, 685.0f,
        -10.0f
    );

    // Restore the original drawing settings
    CP_Settings_Restore();
}


void draw_lose_screen(void) {


    // Colours used for the lose-screen text
    CP_Color title_col = CP_Color_Create(102, 186, 225, 255);
    CP_Color white_col = CP_Color_Create(245, 245, 245, 255);

    CP_Settings_Save();
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_NoStroke();

    // Darken the existing golf course
    draw_rect(
        0.0f, 0.0f,
        (float)SCREEN_WIDTH,
        (float)SCREEN_HEIGHT,
        CP_Color_Create(0, 0, 0, 180)
    );

    // Draw the image using its top-left corner
    CP_Settings_ImageMode(CP_POSITION_CORNER);

    // The entire lose panel is one image, 1400 x 760
    draw_image(
        lose_images[lose_type],
        100.0f, 70.0f,
        1400.0f, 760.0f,
        255
    );

    //=== Start of Title ===
    // Display the title matching the lose condition
    CP_Settings_TextSize(126.0f);

    // Outer shadow (faintest)
    draw_text(
        title_font, CP_Color_Create(255, 255, 255, 25),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_titles[lose_type],
        1029.0f, 209.0f
    );

    // Middle shadow
    draw_text(
        title_font, CP_Color_Create(255, 255, 255, 45),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_titles[lose_type],
        1026.0f, 206.0f
    );

    // Inner shadow (darkest)
    draw_text(
        title_font, CP_Color_Create(255, 255, 255, 80),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_titles[lose_type],
        1023.0f, 203.0f
    );

    // Original title (drawn last, on top)
    CP_Settings_TextSize(126.0f);

    draw_text(
        title_font, title_col,
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_titles[lose_type],
        1020.0f, 200.0f
    ); 
    //=== End of Title ===

    //=== Start of Subtitle ===
    //Display the subtitle matching the lose condition (with drop shadow)
    CP_Settings_TextSize(50.0f);

    // Outer shadow (faintest)
    draw_text(
        body_font, CP_Color_Create(0, 0, 0, 25),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_subtitles[lose_type],
        1106.0f, 371.0f
    );

    // Middle shadow
    draw_text(
        body_font, CP_Color_Create(0, 0, 0, 45),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_subtitles[lose_type],
        1104.0f, 369.0f
    );

    // Inner shadow (darkest)
    draw_text(
        body_font, CP_Color_Create(0, 0, 0, 80),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_subtitles[lose_type],
        1102.0f, 367.0f
    );

    // Original subtitle (drawn on top)
    draw_text(
        body_font, white_col,
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        lose_subtitles[lose_type],
        1100.0f, 365.0f
    ); 
    //=== End of Subtitle ===

    // The interactive Retry and Main Menu buttons
    // are drawn and updated separately in game.c.

    CP_Settings_Restore();
}

// GAMEOVER EXIT
void gameover_exit(void) {

}