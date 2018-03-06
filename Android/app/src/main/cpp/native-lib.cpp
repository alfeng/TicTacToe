#include <jni.h>
#include <sstream>

#include "CTicTacToe.h"

using namespace std;

// The game brain
CTicTacToe tttGame;

// Some Kotlin JNI sites:
// https://proandroiddev.com/android-ndk-interaction-of-kotlin-and-c-c-5e19e35bac74
// https://yalantis.com/blog/android-ndk-the-interaction-between-kotlin-and-c-c-plus-plus/
// https://yalantis.com/blog/android-ndk-calling-kotlin-from-native-code/

template <typename T>
inline std::string toStr(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

// Print to logcat
void logString(string debugStr)
{
    __android_log_write(ANDROID_LOG_VERBOSE, "NATIVE-LIB", debugStr.c_str());
}

extern "C"
{
    // Get a string from C++
    JNIEXPORT jstring JNICALL Java_com_mythica_ticmytac_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */)
    {
        std::string hello = "©2018 Mythica, LLC";
        return env->NewStringUTF(hello.c_str());
    }

    // Check if game over
    JNIEXPORT jint JNICALL Java_com_mythica_ticmytac_MainActivity_isGameOver(JNIEnv *env, jobject obj, jobject rows, jobject cols)
    {
        // Winning row
        std::vector<int> winRows;
        std::vector<int> winCols;

        // Check it
        int winMark = -1;
        bool gameOver = tttGame.IsGameOver(winRows, winCols);
        if (gameOver)
        {
            // Determine type of end game
            winMark = 0;
            if (winRows.size() > 0)
            {
                // Determine winner
                winMark = (int) tttGame.GetMark(winRows[0], winCols[0]);

                // Get ArrayList methods
                jclass arrayListClass = env->FindClass("java/util/ArrayList");
                if (arrayListClass == NULL)
                    logString("----------------- arrayListClass == NULL");
                jmethodID addMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");
                if (addMethod == NULL)
                    logString("----------------- addMethod == NULL");
                jmethodID clearMethod = env->GetMethodID(arrayListClass, "clear", "()V");
                if (clearMethod == NULL)
                    logString("----------------- clearMethod == NULL");

                // Get Integer methods
                jclass integerClass = env->FindClass("java/lang/Integer");
                if (integerClass == NULL)
                    logString("----------------- integerClass == NULL");
                jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");
                if (integerConstructor == NULL)
                    logString("----------------- integerConstructor == NULL");

                // Clear any existing data
                env->CallVoidMethod(rows, clearMethod);
                env->CallVoidMethod(cols, clearMethod);

                // Add current win row data
                logString("----------------- C++ Win Row Data ------------------");
                for (int i = 0;  i < winRows.size();  i++)
                {
                    // Debug it
                    std::ostringstream os1;
                    os1 << "[" << winRows[i] << "," << winCols[i] << "]" << std::endl;
                    logString(os1.str());

                    // Create wrapped Integer objects
                    jobject wrappedRow = env->NewObject(integerClass, integerConstructor, winRows[i]);
                    if (wrappedRow == NULL)
                        logString("----------------- wrappedRow == NULL");
                    jobject wrappedCol = env->NewObject(integerClass, integerConstructor, winCols[i]);
                    if (wrappedCol == NULL)
                        logString("----------------- wrappedCol == NULL");

                    // Add objects to lists
                    bool rcAddRow = (bool) env->CallBooleanMethod(rows, addMethod, wrappedRow);
                    bool rcAddCol = (bool) env->CallBooleanMethod(cols, addMethod, wrappedCol);
                    std::ostringstream os2;
                    os2 << "------------- rcAddRow, rcAddCol = " << rcAddRow << "," << rcAddCol << std::endl;
                    logString(os2.str());

                    // Remove local references
                    env->DeleteLocalRef(wrappedRow);
                    env->DeleteLocalRef(wrappedCol);
                }
            }
        }

        return (jint) winMark;
    }


/*
static thread_local JNIEnv* env;
static jclass java_util_ArrayList = static_cast<jclass>(env->NewGlobalRef(env->FindClass("java/util/ArrayList")));
static jmethodID java_util_ArrayList_= env->GetMethodID(java_util_ArrayList, "<init>", "(I)V");
jmethodID java_util_ArrayList_add = env->GetMethodID(java_util_ArrayList, "add", "(Ljava/lang/Object;)V");

JNIEXPORT jobject JNICALL cppv2javaAL(JNIEnv *env) {

    std::vector<ExampleClass_Cpp> vector;
    jclass J_Class_Example = env->FindClass("app/androidndkproject/ExampleClass");
    jmethodID methodId = env->GetMethodID(J_Class_Example, "<init>", "(I)V");

    jobject result = env->NewObject(java_util_ArrayList, java_util_ArrayList_, vector.size());
    for (auto const &Ex: vector) {
        jobject J_Obj_Example = env->NewObject(J_Class_Example, methodId, Ex.getExampleID(), Ex.getExampleName());
        env->CallVoidMethod(result, java_util_ArrayList_add, J_Obj_Example);
        env->DeleteLocalRef(J_Obj_Example);
    }
    return result;
}
*/


    // Start game over
    JNIEXPORT void JNICALL Java_com_mythica_ticmytac_MainActivity_newGame(JNIEnv *env, jobject /* this */)
    {
        // Start a new game
        tttGame.NewGame();
    }

    // Do human turn
    JNIEXPORT void JNICALL Java_com_mythica_ticmytac_MainActivity_doTurn(JNIEnv *env, jobject obj, jint jRow, jint jCol)
    {
        // Do AI move
        int row = (int) jRow; int col = (int) jCol;
        tttGame.SetMark(row, col, X_MARKER);
    }

    // Do AI turn
    JNIEXPORT void JNICALL Java_com_mythica_ticmytac_MainActivity_doAITurn(JNIEnv *env, jobject obj, jobject objData)
    {
        // Do AI move
        int row = -1, col = -1;
        tttGame.GetBestMove(O_MARKER, row, col);
        tttGame.SetMark(row, col, O_MARKER);

        // Get instance fields
        jclass dataClass = env->GetObjectClass(objData);
        jfieldID rowField = env->GetFieldID(dataClass, "row", "I");
        jfieldID colField = env->GetFieldID(dataClass, "col", "I");

        // Set data
        env->SetIntField(objData, rowField, row);
        env->SetIntField(objData, colField, col);
    }
}
