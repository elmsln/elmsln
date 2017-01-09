import { Component, OnInit } from '@angular/core';
import { FormGroup, FormBuilder } from '@angular/forms';
import { UserService } from '../user.service';
import { Router, ActivatedRoute, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { ActionTypes, loadPermissions } from '../app.actions';
declare const Drupal:any;

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css'],
  providers: [UserService]
})
export class LoginComponent implements OnInit {
  form: FormGroup;

  constructor(
    private fb: FormBuilder,
    private userService: UserService,
    private router: Router,
    private store: Store<{}>
  ) {
    this.form = this.fb.group({
      username: '',
      password: ''
    });
  }

  ngOnInit() {
    // check if we are being loaded within a Drupal site, if we are, skip
    // the basic auth login
    if (typeof Drupal !== 'undefined') {
      console.log('Drupal detected...');
      this.userService.logout();
      this.router.navigate(['/projects']);
    }
  }

  submitForm() {
    // save new critique
    if (this.form.value.username && this.form.value.password) {
      let loggedIn = this.userService.login(this.form.value.username, this.form.value.password);

      this.router.navigate(['/projects']);
    }
  }
}
