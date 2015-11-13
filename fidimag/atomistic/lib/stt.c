#include "clib.h"

//compute (\vec{j}_s \cdot \nabla \vec{m})
void compute_stt_field_c(double *spin, double *field, double *jx, double *jy,
		double dx, double dy, int nx, int ny, int nz, int xperiodic,
		int yperiodic) {

	int nxy = nx * ny;
	int n1 = nz * nxy, n2 = 2 * n1;
	int i, j, k;
	int id, id1, id2;

	for (i = 0; i < 3 * n1; i++) {
		field[i] = 0;
	}

	if (nx > 1) {

        for (k = 0; k < nz; k++) {
			for (j = 0; j < ny; j++) {
                for (i = 1; i < nx - 1; i++) {

					id = nxy * k + nx * j + i;

					id1 = id - 1;
					id2 = id + 1;

					field[3 * id]     += jx[id] * (spin[3 * id2]     - spin[3 * id1])     / (2 * dx);
					field[3 * id + 1] += jx[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (2 * dx);
					field[3 * id + 2] += jx[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (2 * dx);

				}
			}
		}

		// i == 0
		if (xperiodic) {
            for (k = 0; k < nz; k++) {
                for (j = 0; j < ny; j++) {

					//id = nyz * i + nz * j + k;
					id = nxy * k + nx * j;

					id1 = id + (nx - 1);
					id2 = id + 1;

					field[3 * id]     += jx[id] * (spin[3 * id2]     - spin[3 * id1])     / (2 * dx);
					field[3 * id + 1] += jx[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (2 * dx);
					field[3 * id + 2] += jx[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (2 * dx);

				}
			}

		}else{
            for (k = 0; k < nz; k++) {
                for (j = 0; j < ny; j++) {

					//id = nyz * i + nz * j + k;
					id = nxy * k + nx * j;

					id1 = id;
					id2 = id + 1;

					field[3 * id]     += jx[id] * (spin[3 * id2]     - spin[3 * id1])     / (dx);
					field[3 * id + 1] += jx[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (dx);
					field[3 * id + 2] += jx[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (dx);

				}
			}

		}

		// i == nx-1
		if (xperiodic) {
            for (k = 0; k < nz; k++) {
                for (j = 0; j < ny; j++) {

					id = (nx - 1) + nxy * k + nx * j;

					id1 = id - 1;
					id2 = id - (nx - 1);

					field[3 * id]     += jx[id] * (spin[3 * id2]     - spin[3 * id1])     / (2 * dx);
					field[3 * id + 1] += jx[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (2 * dx);
					field[3 * id + 2] += jx[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (2 * dx);

				}
			}

		}else{
            for (k = 0; k < nz; k++) {
                for (j = 0; j < ny; j++) {

					id = (nx - 1) + nxy * k + nx * j;

					id1 = id - 1;
					id2 = id;

					field[3 * id]     += jx[id] * (spin[3 * id2]     - spin[3 * id1])     / (dx);
					field[3 * id + 1] += jx[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (dx);
					field[3 * id + 2] += jx[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (dx);

				}
			}

		}

	} //for nx>1

	if (ny > 1) {

        for (k = 0; k < nz; k++) {
			for (j = 1; j < ny-1; j++) {
                for (i = 0; i < nx; i++) {

                    id = nxy * k + nx * j + i;

					id1 = id - nx;
					id2 = id + nx;

					field[3 * id]      += jy[id] * (spin[3 * id2]     - spin[3 * id1])     / (2 * dy);
					field[3 * id + 1]  += jy[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (2 * dy);
					field[3 * id + 2]  += jy[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (2 * dy);
				}
			}
		}

		// j == 0
		if (yperiodic) {
            for (k = 0; k < nz; k++) {
                for (i = 0; i < nx; i++) {

                    id = nxy * k + i;

					id1 = id + nx * (ny - 1);
					id2 = id + nx;

					field[3 * id]     += jy[id] * (spin[3 * id2]     - spin[3 * id1])     / (2 * dy);
					field[3 * id + 1] += jy[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (2 * dy);
					field[3 * id + 2] += jy[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (2 * dy);
				}
			}
		}else{
            for (k = 0; k < nz; k++) {
                for (i = 0; i < nx; i++) {

                    id = nxy * k + i;

					id1 = id;
					id2 = id + nx;

					field[3 * id]     += jy[id] * (spin[3 * id2]     - spin[3 * id1])     / (dy);
					field[3 * id + 1] += jy[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (dy);
					field[3 * id + 2] += jy[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (dy);
				}
			}

		}


		// j == ny - 1
		if (yperiodic) {
            for (k = 0; k < nz; k++) {
                for (i = 0; i < nx; i++) {

                    id = nxy * k + nx * (ny - 1) + i;

					id1 = id - nx;
					id2 = id - nx * (ny - 1);

					field[3 * id]     += jy[id] * (spin[3 * id2]     - spin[3 * id1])     / (2 * dy);
					field[3 * id + 1] += jy[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (2 * dy);
					field[3 * id + 2] += jy[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (2 * dy);
				}
			}
		}else{
            for (k = 0; k < nz; k++) {
                for (i = 0; i < nx; i++) {

                    id = nxy * k + nx * (ny - 1) + i;

					id1 = id - nx;
					id2 = id;

					field[3 * id]     += jy[id] * (spin[3 * id2]     - spin[3 * id1])     / (dy);
					field[3 * id + 1] += jy[id] * (spin[3 * id2 + 1] - spin[3 * id1 + 1]) / (dy);
					field[3 * id + 2] += jy[id] * (spin[3 * id2 + 2] - spin[3 * id1 + 2]) / (dy);
				}
			}

		}



	} //for ny > 1

}

void llg_stt_rhs(double *dm_dt, double *m, double *h, double *h_stt,
		double *alpha, double beta, double u0, double gamma, int n) {

	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		int j = i + n;
		int k = j + n;

		double coeff = -gamma / (1 + alpha[i] * alpha[i]);

		double mm = m[i] * m[i] + m[j] * m[j] + m[k] * m[k];
		double mh = m[i] * h[i] + m[j] * h[j] + m[k] * h[k];

        //hp=mm.h-mh.m=-mx(mxh)
        double hpi = mm*h[i] - mh*m[i];
        double hpj = mm*h[j] - mh*m[j];
        double hpk = mm*h[k] - mh*m[k];

        double mth0 = cross_x(m[i],m[j],m[k],hpi,hpj,hpk);
        double mth1 = cross_y(m[i],m[j],m[k],hpi,hpj,hpk);
        double mth2 = cross_z(m[i],m[j],m[k],hpi,hpj,hpk);

		dm_dt[i] = coeff * (mth0 - hpi * alpha[i]);
		dm_dt[j] = coeff * (mth1 - hpj * alpha[i]);
		dm_dt[k] = coeff * (mth2 - hpk * alpha[i]);

		//the above part is standard LLG equation.

		double coeff_stt = u0 / (1 + alpha[i] * alpha[i]);

		double mht = m[i] * h_stt[i] + m[j] * h_stt[j] + m[k] * h_stt[k];

		hpi = mm*h_stt[i] - mht * m[i];
		hpj = mm*h_stt[j] - mht * m[j];
		hpk = mm*h_stt[k] - mht * m[k];

        mth0 = cross_x(m[i],m[j],m[k],hpi,hpj,hpk);
        mth1 = cross_y(m[i],m[j],m[k],hpi,hpj,hpk);
        mth2 = cross_z(m[i],m[j],m[k],hpi,hpj,hpk);

		dm_dt[i] += coeff_stt * ((1 + alpha[i] * beta) * hpi
				- (beta - alpha[i]) * mth0);
		dm_dt[j] += coeff_stt * ((1 + alpha[i] * beta) * hpj
				- (beta - alpha[i]) * mth1);
		dm_dt[k] += coeff_stt * ((1 + alpha[i] * beta) * hpk
				- (beta - alpha[i]) * mth2);

		double c = 6 * sqrt(dm_dt[i] * dm_dt[i] + dm_dt[j] * dm_dt[j] + dm_dt[k]* dm_dt[k]);
		dm_dt[i] += c * (1 - mm) * m[i];
		dm_dt[j] += c * (1 - mm) * m[j];
		dm_dt[k] += c * (1 - mm) * m[k];

	}

}

