import { Component, OnInit, Input, OnChanges } from '@angular/core';
import { Router } from '@angular/router';
import { Submission } from '../submission';
import { UserService } from '../../user.service';


@Component({
  selector: 'app-submission-list',
  templateUrl: './submission-list.component.html',
  styleUrls: ['./submission-list.component.css']
})
export class SubmissionListComponent implements OnInit, OnChanges {
  @Input() submissions:Submission[];
  @Input() title:string;
  currentUserId:number;

  constructor(
    private router:Router,
    private userService:UserService
  ) { }

  ngOnInit() {
    this.userService.getCurrentUserId()
      .subscribe(uid => this.currentUserId = uid)
  }

  ngOnChanges() {
  }

  onSubmissionClick(submission:Submission) {
    this.router.navigate(['/submissions/' + submission.id]);
  }

}
