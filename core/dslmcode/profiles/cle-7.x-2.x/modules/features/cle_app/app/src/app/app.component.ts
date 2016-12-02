import { Component, OnInit } from '@angular/core';
import { UserService } from './user.service';
import { Router, ActivatedRoute, Params } from '@angular/router';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  providers: [UserService]
})
export class AppComponent implements OnInit {
  constructor(
    private router: Router,
  ) { }
  ngOnInit() {
    // Find out if the user is already logged In
    let auth = localStorage.getItem('basicAuthCredentials');
    if (auth) {
      this.router.navigate(['/projects']);
    }
    else {
      this.router.navigate(['/login']);
    }
  }
}