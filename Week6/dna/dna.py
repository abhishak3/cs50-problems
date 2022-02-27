import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("USAGE: python database.csv sequence.txt")
        return 0

    # TODO: Read database file into a variable
    db_filename = sys.argv[1]
    db = []
    with open(db_filename, 'r') as db_file:
        x = csv.DictReader(db_file)

        # converting STR count to integer type
        for i in x:
            for j in i.keys():
                if j != 'name':
                    i[j] = int(i[j])
            db.append(i)

    # TODO: Read DNA sequence file into a variable
    sq_filename = sys.argv[2]
    with open(sq_filename, 'r') as sq_file:
        sq = sq_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    sequences = list(db[0].keys())[1:]
    seq_count = {}
    for seq in sequences:
        seq_count[seq] = longest_match(sq, seq)

    # TODO: Check database for matching profiles
    for i in db:
        if(tuple(i.values())[1:] == tuple(seq_count.values())):
            print(i["name"])
            return
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
