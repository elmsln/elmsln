import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'cle-user',
  templateUrl: './user.component.html',
  styleUrls: ['./user.component.css']
})
export class UserComponent implements OnInit {
  username: string = 'restws_admin';
  password: string = 'admin';

  constructor() { }

  ngOnInit() {
  }

}
