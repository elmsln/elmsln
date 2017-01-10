import { Component, OnInit, Input } from '@angular/core';
import { Router } from '@angular/router';
import { Submission } from '../submission';

@Component({
  selector: 'app-submission-list',
  templateUrl: './submission-list.component.html',
  styleUrls: ['./submission-list.component.css']
})
export class SubmissionListComponent implements OnInit {
  @Input() submissions:Submission[];
  @Input() title:string;

  constructor(
    private router:Router
  ) { }

  ngOnInit() {
  }

  onSubmissionClick(submission:Submission) {
    this.router.navigate(['/submissions/' + submission.id]);
  }

}
