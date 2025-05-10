## ✅ **HPC Viva Questions (25)**

### 🔹 **General Parallel Programming & OpenMP (Q1–Q5)**

1. **What is parallel computing?**
   → Executing multiple tasks at the same time using multiple cores or processors.

2. **What is OpenMP?**
   → An API for writing parallel programs in C/C++ and Fortran for shared-memory systems.

3. **What does `#pragma omp parallel` do?**
   → It creates multiple threads that execute the enclosed code block in parallel.

4. **What is a race condition?**
   → When two threads access the same resource at the same time, causing unpredictable results.

5. **What is a critical section in OpenMP?**
   → A block of code that only one thread can execute at a time to avoid race conditions.

---

### 🔹 **HPC 1: Parallel BFS and DFS (Q6–Q10)**

6. **What is BFS?**
   → Breadth-First Search explores neighbors level-by-level using a queue.

7. **What is DFS?**
   → Depth-First Search explores as far as possible down a path before backtracking using recursion or stack.

8. **How do you parallelize BFS in OpenMP?**
   → By parallelizing the loop over each node’s neighbors using `#pragma omp parallel for`.

9. **Why is DFS difficult to parallelize?**
   → Because of recursion and shared visited array, which can lead to race conditions.

10. **Is BFS output always the same in parallel?**
    → No, due to non-deterministic thread scheduling, the order may vary.

---

### 🔹 **HPC 2: Parallel Bubble and Merge Sort (Q11–Q15)**

11. **What is bubble sort?**
    → A simple algorithm that repeatedly swaps adjacent elements if they’re in the wrong order.

12. **How is bubble sort parallelized?**
    → Using odd-even transposition, where non-conflicting elements are swapped in parallel.

13. **What is merge sort?**
    → A divide-and-conquer algorithm that recursively splits the array and merges sorted parts.

14. **How is merge sort parallelized using OpenMP?**
    → Using `#pragma omp sections` to sort left and right halves in separate threads.

15. **Which is more efficient to parallelize: merge sort or bubble sort? Why?**
    → Merge sort, because it naturally divides into independent subproblems.

---

### 🔹 **HPC 3: Parallel Reduction (Q16–Q20)**

16. **What is reduction in OpenMP?**
    → Combining results from multiple threads into a single variable (e.g., sum, min, max).

17. **How do you find the average using reduction?**
    → Sum all elements using `reduction(+:sum)` and divide by number of elements.

18. **Can you perform multiple reductions in the same loop?**
    → Yes, e.g., `reduction(+:sum) reduction(min:minVal)`

19. **What are the limitations of parallel reduction?**
    → It can’t handle operations that are not associative or depend on ordering.

20. **What is the default scheduling in OpenMP loops?**
    → Static, unless otherwise specified.

---

### 🔹 **HPC 4: CUDA Programming (Q21–Q25)**

21. **What is CUDA?**
    → A parallel computing platform and API by NVIDIA for GPU programming.

22. **What are kernels in CUDA?**
    → Functions that run on the GPU, executed by many threads in parallel.

23. **What is a thread block?**
    → A group of threads that execute a CUDA kernel and share memory.

24. **What is the difference between host and device code?**
    → Host code runs on CPU; device code (kernels) runs on GPU.

25. **Which applications benefit from GPU acceleration?**
    → Matrix multiplication, vector operations, image processing, ML, etc.

---

## ✅ **Deep Learning Viva Questions (25)**

### 🔹 **DL1: Linear Regression with DNN (Q26–Q30)**

26. **What is regression in ML?**
    → Predicting continuous values (e.g., price, temperature).

27. **What is the loss function used in linear regression?**
    → Mean Squared Error (MSE).

28. **Why use DNN for linear regression?**
    → To learn complex relationships if simple linearity is insufficient.

29. **Which activation function is used in output layer?**
    → None or linear (since output is continuous).

30. **What metric is used to evaluate regression?**
    → Mean Absolute Error (MAE), Mean Squared Error (MSE).

---

### 🔹 **DL2: Classification with DNN (OCR Dataset) (Q31–Q35)**

31. **What is multiclass classification?**
    → Predicting one of several classes (e.g., letters A-Z).

32. **What is softmax activation used for?**
    → Converts raw scores into probabilities in multiclass output.

33. **What is one-hot encoding?**
    → A method to represent class labels as binary vectors.

34. **Which loss function is used for multiclass classification?**
    → Categorical crossentropy.

35. **Why use label encoding + one-hot for OCR?**
    → Neural nets need numeric + probability-friendly format.

---

### 🔹 **DL3: CNN on Fashion MNIST (Q36–Q40)**

36. **What is CNN?**
    → A type of neural network good for image data, using filters and pooling.

37. **What does a Conv2D layer do?**
    → Applies convolutional filters to detect patterns in images.

38. **What is pooling in CNN?**
    → Reduces image size (max/avg) to retain features and speed up training.

39. **Why reshape images to (28,28,1)?**
    → To match CNN input format: height x width x channels.

40. **How many classes are in Fashion MNIST?**
    → 10 classes (e.g., T-shirt, sneaker, dress, etc.)

---

### 🔹 **DL4: Real-World Projects (Q41–Q50)**

41. **What is face recognition?**
    → Identifying or verifying individuals using facial features.

42. **What dataset is used for face recognition?**
    → Common ones: LFW, VGGFace, or custom datasets.

43. **How does age/gender detection work?**
    → CNN predicts probabilities for age group and gender.

44. **What is the output of a gender classifier?**
    → A binary class: male or female.

45. **How do you colorize black and white images?**
    → Train a CNN to predict RGB values from grayscale input.

46. **What is the challenge in colorizing images?**
    → One input (gray) → many possible colors (ambiguity).

47. **What is transfer learning?**
    → Reusing pre-trained models (like VGG) for related tasks.

48. **What library is commonly used for DL?**
    → TensorFlow or PyTorch.

49. **What is early stopping?**
    → Stopping training when validation loss stops improving.

50. **Why use dropout in DL models?**
    → To prevent overfitting by randomly deactivating neurons during training.
