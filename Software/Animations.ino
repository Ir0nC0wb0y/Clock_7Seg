void animation_cycle() {
  if (grad_hr == 0) {
    grad_dir_hr = 1;
  } else if (grad_hr == 250) {
    grad_dir_hr = -1;
  }
  grad_hr = grad_hr + grad_dir_hr;

  if (grad_mn == 0) {
    grad_dir_mn = 1;
  } else if (grad_mn == 250) {
    grad_dir_mn = -1;
  }
  grad_mn = grad_mn + grad_dir_mn;
}
