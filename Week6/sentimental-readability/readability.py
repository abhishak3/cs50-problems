# getting user input
sentence = input("Text: ")

lettersT = wordsT = sentencesT = i = 0
lettersPH = sentencesPH = 0

# traversing through sentence
for i in range(len(sentence)):

    # determing the end of sentence
    if sentence[i] in ['.', '!', '?']:
        sentencesT += 1

    # determining letters
    elif sentence[i].isalpha():
        lettersT += 1

    # determining words
    elif sentence[i] == ' ':
        wordsT += 1

# Adding the last word in the sentence
wordsT += 1

# calculating letters per hundred words
lettersPH = (lettersT / wordsT) * 100

# calculating sentences per hundred words
sentencesPH = (sentencesT / wordsT) * 100

# rounding off to nearest integer
grade = int((0.0588 * lettersPH - 0.296 * sentencesPH - 15.8) + 0.5)

# Display respective grades
if grade < 1:
    print("Before Grade 1")

elif grade >= 16:
    print("Grade 16+\n")

else:
    print("Grade", grade)