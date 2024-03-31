int* plusOne(int* digits, int digitsSize, int* returnSize) {
    // Carry variables are used to represent the carry in the add one operation
    int carry = 1; // Initialize the carry to 1, as we want to add 1 to the last digit of the array
    int* result = (int*)malloc(sizeof(int)*(digitsSize + 1));// Allocate memory space for the result array, as the highest digit may carry, so allocate space for digitsSize + 1
    int* resultPtr = result + digitsSize; // Initialize a pointer to the last digit of the result array
    int* digitsPtr = digits + digitsSize; // Initialize a pointer to the last digit of the input array digits

    // Traverse from the end of the array, add the value of digits to carry, and then perform the carry calculation, adding carry to each digit (initially 1, that is, add one operation)
    for (int i = 0; i < digitsSize; i++) {
        --digitsPtr; // Move the pointer to the previous digit
        *resultPtr = (*digitsPtr + carry) % 10; // Add the digit and carry, and take the modulo to get the result of the current digit
        carry = (*digitsPtr + carry) / 10; // Calculate whether there is a carry to the next digit
        --resultPtr; // Move the result pointer to the next position to accept the result of the next digit
    }

    if (carry > 0) { // If the highest digit has a carry, the result array needs to be extended by one digit
        *returnSize = digitsSize + 1; // Update the return size to digitsSize + 1
        *result = 1; // Since it is an add one operation, the new highest digit must be 1
        for (int i = 1; i < *returnSize; i++) {// Initialize the remaining digits to 0 starting from the second digit of the result
            *(result + i) = 0; // Set other digits to 0
        }
    } else { // If there is no carry, the return size remains the same, and the result array does not need to be extended
        *returnSize = digitsSize;
        result++; // Move the pointer of the result forward to remove the leading 0
    }

    return result;// Return the pointer to the result array
}
