void read_matrix (char* file_name, int n, int m, float** matrix)
{
	FILE * src_file; fopen_s(&src_file, file_name, "rb");

	if (!src_file) {
		fclose(src_file);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(src_file, "\t%e", &matrix[i][j]);
		}
		fscanf(src_file, "\t\n");
	}

	fclose(src_file);

	return;
}